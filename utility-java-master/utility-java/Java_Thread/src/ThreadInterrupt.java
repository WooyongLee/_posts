/*
// InterruptedException Ã³¸®
class InterruptedThread extends Thread {
	boolean suspended = false;
	boolean closed = false;
	
	@Override
	public void run() {
		while (!closed) {
			if(suspended) {
				synchronized(this) {
					try{
						wait();
					}
					catch (InterruptedException e ) {
					}
				}
			}
			try {
				Thread.sleep(400);
			} catch (InterruptedException e) {
				System.out.println("interruped..");
			}
		}
	}
	public void mySuspend() {
		suspended = true;
		
		System.out.println("mySuspend:interruping...");
		interrupt();
	}
	
	public void myResume() {
		suspended = false;
		
		synchronized(this) {
			notify();
		}
	}
	public void close() {
		closed = true;
		
		interrupt();
	}
}

public class ThreadInterrupt {
	public static void main(String[] args)	throws Exception {
		// Thread Test
		InterruptedThread thread = new InterruptedThread();
		
		thread.start();
		thread.mySuspend();
		Thread.sleep(4000);
		thread.myResume();
		thread.close();
		thread.join();
	}
}
*/
