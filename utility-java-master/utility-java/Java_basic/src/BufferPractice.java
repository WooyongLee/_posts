/*
import java.nio.ByteBuffer;

public class BufferPractice {
	public BufferPractice() {	}
	public static void main(String[] args) {
		int buffersize = 4096;
		
		// buffersize�� ����Ʈ���� �Ҵ�
		ByteBuffer bb = ByteBuffer.allocate(buffersize);
	
		try {
			bb.putChar('\n');
			bb.putChar('j');
			bb.putChar(' ');
			bb.putInt(300);
			
			// ������ ��ġ�� ó������ �ű�
			bb.rewind();
			
			// ���ۿ��� ������ ���� ����ϱ�
			System.out.print("Buffer : " + bb.getChar() + bb.getChar() + bb.getChar()  + bb.getInt());

			// ����Ʈ���� �ʱ�ȭ
			bb.clear();
		} catch (Exception e) {
			e.printStackTrace();
		}
		
	}

}*/
