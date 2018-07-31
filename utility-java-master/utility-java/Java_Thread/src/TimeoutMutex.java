
public class TimeoutMutex {
	// 빈 쓰레드 생성
	Thread locker = null;

	public void lock(long timeout) throws TimeoutException {
		// 인터럽트의 여부 판단용 변수
		boolean interrupted = false;
		long startTime = 0, endTime = 0;
		
		synchronized(this) {
			// 쓰레드 locker가 들어왔을 경우 해당 인터럽트 수행시간 체크
			if (locker != null) {
				try {
					startTime = System.currentTimeMillis();
					wait(timeout);
					endTime = System.currentTimeMillis();
				} catch (InterruptedException e) {
					interrupted = true;
				}
			} // end if
		}  // end synch
		
		System.out.println("[" + Thread.currentThread() + "][" +this + "]Waiting Time :" + (endTime - startTime));
		
		// timeout되었고, locking이 실패하는 경우(예외처리, 거의 발생할 경우 없다고 봐도 됨)
		if ( (endTime - startTime) >= timeout) {
			throw new TimeoutException();
		}
		
		locker = Thread.currentThread();
		
		//
		if ( interrupted) {
			// 쓰레드에 인터럽트 걸어주기
			locker.interrupt();
		}
	} 
	
	public void unlock() {
		synchronized(this) {
			if (!locker.equals(Thread.currentThread())) {
				throw new IllegalMonitorStateException( 
					"TimeoutMutex.unlock() : Not owner");
			}
			// 쓰레드 해제, 자원 반납
			locker = null;
			notify();
		}
	}
}

class TimeoutException extends Exception {
	public TimeoutException() {
		this("TimeoutException");
	}
	public TimeoutException(String s) {
		super(s);
	}
}
