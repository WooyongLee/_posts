/*
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.IOException;

public class StringCompare {
	public static void main(String[] args) {
		String sourceString = "This is source string";
		
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader reader = new BufferedReader(isr);
		// string buffer ��ü ����, ��Ʈ���� ���۸��Ͽ� ���� �Է��� ȿ�������� ���ش�.
		String line = null;
		
		System.out.println("Source string>" + sourceString);
		try {
			while ((line = reader.readLine()) != null) {
			// readLine �޼ҵ� :: ������ �д´�. "\n", "\r"�� ������ ���� �о�´�(�Է��� �����鼭 \n ġ�� �ڵ� while�� ���� ����)
			
				System.out.println("Inputed string> "+ line); // input�� string ����غ���
				System.out.println(sourceString.indexOf(line)); // string�� �ε��� ��ȣ ��������
				
				// ������ ��ġ�� ���
				if ( sourceString.compareTo(line) == 0 )
					System.out.println("equal");
					
				// ������ �ε��� ��ȣ �ִ� ���, ��ġ�ϴ� �ε��� �ִ� ���
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
