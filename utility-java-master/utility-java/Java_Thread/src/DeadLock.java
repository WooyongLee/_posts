// ������� ������ ��Ȳ�� ������
/*
public class DeadLock {
	public static void main(String[] args) throws Exception {
		Mutex mutex1 = new Mutex();
		Mutex mutex2 = new Mutex();
		
		DeadLockThread1 thread1 = new DeadLockThread1();
		DeadLockThread2 thread2 = new DeadLockThread2();
		
		thread1.set(mutex1, mutex2);
		thread2.set(mutex1, mutex2);
		thread1.start();
		thread2.start();
		
		thread1.join();
		thread2.join();
	}
}

class DeadLockThread1 extends Thread {
	Mutex mutex1 = null;
	Mutex mutex2 = null;
	
	public void run() {
		try {
			System.out.println("[DeadLockThread1] Entering mutex1");
			mutex1.lock();
			// �� �����尡 mutex, mutex2�� ��� ȹ���ϰ� �����ϴ� ���� ����
			Thread.sleep(100);
			System.out.println("[DeadLockThread1] Entering mutex2");
			mutex2.lock();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public void set(Mutex m1, Mutex m2) {
		mutex1 = m1;
		mutex2= m2;
	}
}

class DeadLockThread2 extends Thread {
	Mutex mutex1 = null;
	Mutex mutex2 = null;
	
	public void run() {
		try {
			System.out.println("[DeadLockThread2] Entering mutex2");
			mutex2.lock();
			// �� �����尡 mutex, mutex2�� ��� ȹ���ϰ� �����ϴ� ���� ����
			Thread.sleep(100);
			System.out.println("[DeadLockThread2] Entering mutex1");
			mutex1.lock();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	public void set(Mutex m1, Mutex m2) {
		mutex1 = m1;
		mutex2 = m2;
	}
}
*/

