
public class TimeoutMutex {
	// �� ������ ����
	Thread locker = null;

	public void lock(long timeout) throws TimeoutException {
		// ���ͷ�Ʈ�� ���� �Ǵܿ� ����
		boolean interrupted = false;
		long startTime = 0, endTime = 0;
		
		synchronized(this) {
			// ������ locker�� ������ ��� �ش� ���ͷ�Ʈ ����ð� üũ
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
		
		// timeout�Ǿ���, locking�� �����ϴ� ���(����ó��, ���� �߻��� ��� ���ٰ� ���� ��)
		if ( (endTime - startTime) >= timeout) {
			throw new TimeoutException();
		}
		
		locker = Thread.currentThread();
		
		//
		if ( interrupted) {
			// �����忡 ���ͷ�Ʈ �ɾ��ֱ�
			locker.interrupt();
		}
	} 
	
	public void unlock() {
		synchronized(this) {
			if (!locker.equals(Thread.currentThread())) {
				throw new IllegalMonitorStateException( 
					"TimeoutMutex.unlock() : Not owner");
			}
			// ������ ����, �ڿ� �ݳ�
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
