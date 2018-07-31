/*
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.io.ObjectInputStream;
import java.util.StringTokenizer;
import java.io.Serializable;
class MyString implements Serializable {
	private String content;
	public MyString(String myString) {
		setString(myString);
	}
	
	//StringTokenizer는 직렬화 되어 있지 않음, writeObject, readObject 메소드에서 직렬화 시켜주어야 함
//	private StringTokenizer st = new StringTokenizer("Test", " ");
	private String delimiter = new String(" ");
	private StringTokenizer st;
	
	public void setString(String myString){
		content = myString;
	}
	public String toString() {
		return "[MyString]" + content;
	}
	
	private void writeObject(java.io.ObjectOutputStream out) throws IOException {
		// 저장하기
		out.writeObject(content);
		out.writeObject(delimiter);
	}
	
	private void readObject(java.io.ObjectInputStream in) throws IOException, ClassNotFoundException {
		// 불러오기
		content = (String)in.readObject();
		delimiter = (String)in.readObject();
		
		// StringTokenizer는 직렬화 되지 않아 파일에 객체를 저장하거나 불러드릴 수 없기 때문에 새 객체를 생성
		st = new StringTokenizer( toString(), delimiter);
	}
}

public class Serialize {
	public static void main(String[] args) {
		try {
			MyString writeString = new MyString("This is Serialized Object");
			
			// 저장하기
			FileOutputStream fout = new FileOutputStream("string.obj");
			ObjectOutputStream oout = new ObjectOutputStream(fout);
			oout.writeObject(writeString);
			oout.close();
			
			// 읽어오기
			FileInputStream fin = new FileInputStream("string.obj");
			ObjectInputStream oin = new ObjectInputStream(fin);
			Object o = oin.readObject();
			MyString readString = (MyString)o;
			oin.close();
			
			System.out.println(readString);
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
}
*/
