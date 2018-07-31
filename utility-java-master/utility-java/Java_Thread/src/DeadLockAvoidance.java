// DeadLock�� ȸ���ϴ� ��Ȳ�� ����� �ùķ��̼� ��
// with TimeoutMutex.class
public class DeadLockAvoidance {
	public static void main(String[] args) throws Exception {
		TimeoutMutex mutex1 = new TimeoutMutex();
		TimeoutMutex mutex2 = new TimeoutMutex();
		
		DeadLockAvoidanceThread1 thread1 = new DeadLockAvoidanceThread1();
		DeadLockAvoidanceThread2 thread2 = new DeadLockAvoidanceThread2();
		
		thread1.set(mutex1, mutex2);
		thread2.set(mutex1, mutex2);
		thread1.start();
		thread2.start();
		
		thread1.join();
		thread2.join();
	}
}
class DeadLockAvoidanceThread1 extends Thread {
	TimeoutMutex mutex1 = null;
	TimeoutMutex mutex2 = null;
	
	public void run() {
		try{
			System.out.println("[DeadLockAvoidanceThread1] Entering mutex1");
			mutex1.lock(5000);
			// �� �����尡 mutex, mutex2�� ��� ȹ���ϰ� �����ϴ� ���� ����
			Thread.sleep(100);
			System.out.println("[DeadLockAvoidanceThread1] Entering mutex2");
			mutex2.lock(5000);

			// mutex2 �ڿ� �ݳ�
			try {
				System.out.println("[DeadLockAvoidanceThread1] Exit mutex2");
				mutex2.unlock();
			} catch (Exception e){
				e.printStackTrace();
			}
			
			// mutex1 �ڿ� �ݳ�
			try {
				System.out.println("[DeadLockAvoidanceThread1] Exit mutex1");
				mutex1.unlock();
			} catch (Exception e){
				e.printStackTrace();
			}
			
		} catch(TimeoutException e) {
			try {
				System.out.println("[DeadLockAvoidanceThread1] Exit mutex2");
				mutex2.unlock();
			} catch(Exception ee) {
				ee.printStackTrace();
			}
			
			try {
				System.out.println("[DeadLockAvoidanceThread1] Exit mutex1");
				mutex1.unlock();
			} catch(Exception ee) {
				ee.printStackTrace();
			}
		
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}		
	}
	public void set (TimeoutMutex m1, TimeoutMutex m2) {
		mutex1 = m1;
		mutex2 = m2;
	}
}

class DeadLockAvoidanceThread2 extends Thread {
	TimeoutMutex mutex1;
	TimeoutMutex mutex2;
	
	public void run() {
		try{
			System.out.println("[DeadLockAvoidanceThread2] Entering mutex2");
			mutex2.lock(5000);
			// �� �����尡 mutex, mutex2�� ��� ȹ���ϰ� �����ϴ� ���� ����
			Thread.sleep(100);
			System.out.println("[DeadLockAvoidanceThread2] Entering mutex1");
			mutex1.lock(5000);

			// mutex2 �ڿ� �ݳ�
			try {
				System.out.println("[DeadLockAvoidanceThread2] Exit mutex1");
				mutex1.unlock();
			} catch (Exception e){
				e.printStackTrace();
			}
			
			// mutex1 �ڿ� �ݳ�
			try {
				System.out.println("[DeadLockAvoidanceThread2] Exit mutex2");
				mutex2.unlock();
			} catch (Exception e){
				e.printStackTrace();
			}
			
		} catch(TimeoutException e) {
			try {
				System.out.println("[DeadLockAvoidanceThread2] Exit mutex1");
				mutex1.unlock();
			} catch(Exception ee) {
				ee.printStackTrace();
			}
			
			try {
				System.out.println("[DeadLockAvoidanceThread2] Exit mutex2");
				mutex2.unlock();
			} catch(Exception ee) {
				ee.printStackTrace();
			}
		
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}		
	}
	public void set (TimeoutMutex m1, TimeoutMutex m2) {
		mutex1 = m1;
		mutex2 = m2;
	}
}