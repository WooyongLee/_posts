package com.example.administrator.mobiletermproject;

import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.ListView;

import com.example.administrator.mobiletermproject.R;

import java.util.ArrayList;

public class LibraryActivity extends AppCompatActivity {
    private ListView m_ListView1,m_ListView2,m_ListView3,m_ListView4;//메모를 나열할 리스트 뷰
    private ArrayAdapter<String> m_Adapter1,m_Adapter2,m_Adapter3,m_Adapter4; //리스트뷰에 쓰일 어댑터
    public ArrayList<String> nameOfFile= new ArrayList<String>();//파일명을 저장할 ArrayList
    //테스트용
    public ArrayList<String> nameOfFile2= new ArrayList<String>();//파일명을 저장할 ArrayList
    //타이틀변경 테스트용
    public String str="123";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_library);
        //타이틀 변경
        setTitle("str");
        //리스트뷰 네개를 어댑터와 연결하는 함수
        setListViews();
    }

    /*
    클래스 하나만들어서 리스트뷰의 제목대로 저장되어 분류된 폴더명을 바탕으로 해당리스트뷰 생성하는 객체지향 코드 짜보자
     */
    public void setListViews(){
        //테스트할 텍스트 입력
        nameOfFile.add("test1");
        nameOfFile.add("test1");
        nameOfFile.add("test1");
        nameOfFile.add("test1");
        nameOfFile.add("test1");
        nameOfFile.add("test1");nameOfFile.add("test1");
        nameOfFile.add("test1");
        nameOfFile.add("test1");nameOfFile.add("test1");
        nameOfFile.add("test1");
        nameOfFile.add("test1");nameOfFile.add("test1");
        nameOfFile.add("test1");
        nameOfFile.add("test1");
        nameOfFile2.add("서정민 븅씬");

        //첫번째 리스트
        // Android에서 제공하는 String 문자열 하나를 출력하는 layout으로 어댑터 생성
        m_Adapter1 = new ArrayAdapter<String>(this, R.layout.library_listview_items, nameOfFile);
        // Xml에서 추가한 ListView의 객체를 사용
        m_ListView1 = (ListView) findViewById(R.id.list1);
        m_ListView1.setAdapter(m_Adapter1);
        // ListView 아이템 터치 시 이벤트를 처리할 리스너 설정
        //m_ListView.setOnItemClickListener(onClickListItem);

        //리스트뷰 속성
        m_ListView1.setOverScrollMode(View.OVER_SCROLL_IF_CONTENT_SCROLLS);//화면을 넘어가면 스크롤바 생성
        m_ListView1.setDivider((new ColorDrawable(Color.GRAY)));//구분선 회색
        m_ListView1.setDividerHeight(5);//구분선 굵기

        //두번째 리스트
        // Android에서 제공하는 String 문자열 하나를 출력하는 layout으로 어댑터 생성
        m_Adapter2 = new ArrayAdapter<String>(this, R.layout.library_listview_items, nameOfFile);
        // Xml에서 추가한 ListView의 객체를 사용
        m_ListView2 = (ListView) findViewById(R.id.list2);
        m_ListView2.setAdapter(m_Adapter2);
        // ListView 아이템 터치 시 이벤트를 처리할 리스너 설정
        //m_ListView.setOnItemClickListener(onClickListItem);

        //리스트뷰 속성
        m_ListView2.setOverScrollMode(View.OVER_SCROLL_IF_CONTENT_SCROLLS);//화면을 넘어가면 스크롤바 생성
        m_ListView2.setDivider((new ColorDrawable(Color.GRAY)));//구분선 회색
        m_ListView2.setDividerHeight(5);//구분선 굵기

        //세번째 리스트
        // Android에서 제공하는 String 문자열 하나를 출력하는 layout으로 어댑터 생성
        m_Adapter3 = new ArrayAdapter<String>(this, R.layout.library_listview_items, nameOfFile);
        // Xml에서 추가한 ListView의 객체를 사용
        m_ListView3 = (ListView) findViewById(R.id.list3);
        m_ListView3.setAdapter(m_Adapter3);
        // ListView 아이템 터치 시 이벤트를 처리할 리스너 설정
        //m_ListView.setOnItemClickListener(onClickListItem);

        //리스트뷰 속성
        m_ListView3.setOverScrollMode(View.OVER_SCROLL_IF_CONTENT_SCROLLS);//화면을 넘어가면 스크롤바 생성
        m_ListView3.setDivider((new ColorDrawable(Color.GRAY)));//구분선 회색
        m_ListView3.setDividerHeight(5);//구분선 굵기

        //네번째 리스트
        // Android에서 제공하는 String 문자열 하나를 출력하는 layout으로 어댑터 생성
        m_Adapter4 = new ArrayAdapter<String>(this, R.layout.library_listview_items, nameOfFile2);
        // Xml에서 추가한 ListView의 객체를 사용
        m_ListView4 = (ListView) findViewById(R.id.list4);
        m_ListView4.setAdapter(m_Adapter4);
        // ListView 아이템 터치 시 이벤트를 처리할 리스너 설정
        //m_ListView.setOnItemClickListener(onClickListItem);

        //리스트뷰 속성
        m_ListView4.setOverScrollMode(View.OVER_SCROLL_IF_CONTENT_SCROLLS);//화면을 넘어가면 스크롤바 생성
        m_ListView4.setDivider((new ColorDrawable(Color.GRAY)));//구분선 회색
        m_ListView4.setDividerHeight(5);//구분선 굵기


    }

    //메뉴생성
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.menu_library, menu);
        return true;
    }

    //액션바의 메뉴 버튼 리스너
    /*
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        if(item.getItemId()== R.id.menuCreateMemo){//메모 생성 버튼 클릭시
            Intent intent = new Intent(MainActivity.this, CreateActivity.class);
            startActivityForResult(intent,1);
        }
        else if(item.getItemId()== R.id.menuDeleteAll){//전체 삭제 버튼 클릭시
            //경고 대화상자 생성
            final AlertDialog.Builder popup = new AlertDialog.Builder(MainActivity.this);
            popup.setTitle("CAUTION");
            popup.setMessage("All MEMOS will be delete. Are you sure?");
            popup.setPositiveButton("YES", new DialogInterface.OnClickListener() {//yes 선택시
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    while(nameOfFile.size()!=0){//arraylist가 빌 때 까지 파일삭제 및 arraylist 제거연산 수행
                        deleteFile(nameOfFile.get(0));
                        nameOfFile.remove(0);
                    }
                    dialog.dismiss();
                    onResume();//메인 엑티비티 업데이트
                }
            });
            popup.setNegativeButton("NO", new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {//no 선택시
                    //Toast.makeText(getApplicationContext(), "No Clicked", Toast.LENGTH_LONG).show();
                    dialog.dismiss();
                }
            });
            popup.setIcon(R.drawable.alert);//대화창 아이콘 설정
            popup.create();
            popup.show();
        }
        return true;
    }
    */
}
