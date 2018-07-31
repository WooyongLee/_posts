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
	
	//StringTokenizer�� ����ȭ �Ǿ� ���� ����, writeObject, readObject �޼ҵ忡�� ����ȭ �����־�� ��
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
		// �����ϱ�
		out.writeObject(content);
		out.writeObject(delimiter);
	}
	
	private void readObject(java.io.ObjectInputStream in) throws IOException, ClassNotFoundException {
		// �ҷ�����
		content = (String)in.readObject();
		delimiter = (String)in.readObject();
		
		// StringTokenizer�� ����ȭ ���� �ʾ� ���Ͽ� ��ü�� �����ϰų� �ҷ��帱 �� ���� ������ �� ��ü�� ����
		st = new StringTokenizer( toString(), delimiter);
	}
}

public class Serialize {
	public static void main(String[] args) {
		try {
			MyString writeString = new MyString("This is Serialized Object");
			
			// �����ϱ�
			FileOutputStream fout = new FileOutputStream("string.obj");
			ObjectOutputStream oout = new ObjectOutputStream(fout);
			oout.writeObject(writeString);
			oout.close();
			
			// �о����
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
