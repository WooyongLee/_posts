/*
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.IOException;

public class StringCompare {
	public static void main(String[] args) {
		String sourceString = "This is source string";
		
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader reader = new BufferedReader(isr);
		// string buffer 객체 생성, 스트링을 버퍼링하여 문자 입력을 효율적으로 해준다.
		String line = null;
		
		System.out.println("Source string>" + sourceString);
		try {
			while ((line = reader.readLine()) != null) {
			// readLine 메소드 :: 한줄을 읽는다. "\n", "\r"을 만날때 까지 읽어온다(입력을 받으면서 \n 치면 자동 while문 내부 실행)
			
				System.out.println("Inputed string> "+ line); // input한 string 출력해보기
				System.out.println(sourceString.indexOf(line)); // string의 인덱스 번호 가져오기
				
				// 완전히 일치할 경우
				if ( sourceString.compareTo(line) == 0 )
					System.out.println("equal");
					
				// 라인의 인덱스 번호 있는 경우, 일치하는 인덱스 있는 경우
				else if (sourceString.indexOf(line) >= 0)
					System.out.println("substring");
				else
					System.out.println("no");
				
			}
		} catch(IOException e) {
			e.printStackTrace();
		}
		
	}
}
*/
