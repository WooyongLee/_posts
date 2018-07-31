/*
import java.nio.ByteBuffer;

public class BufferPractice {
	public BufferPractice() {	}
	public static void main(String[] args) {
		int buffersize = 4096;
		
		// buffersize로 바이트버퍼 할당
		ByteBuffer bb = ByteBuffer.allocate(buffersize);
	
		try {
			bb.putChar('\n');
			bb.putChar('j');
			bb.putChar(' ');
			bb.putInt(300);
			
			// 버퍼의 위치를 처음으로 옮김
			bb.rewind();
			
			// 버퍼에서 가져온 내용 출력하기
			System.out.print("Buffer : " + bb.getChar() + bb.getChar() + bb.getChar()  + bb.getInt());

			// 바이트버퍼 초기화
			bb.clear();
		} catch (Exception e) {
			e.printStackTrace();
		}
		
	}

}*/
