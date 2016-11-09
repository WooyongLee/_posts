package com.example.administrator.mobiletermproject;

import android.content.DialogInterface;
import android.content.Intent;
import android.content.res.Configuration;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.os.Bundle;
import android.os.Environment;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.Toast;

import java.io.File;
import java.io.FilenameFilter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.LinkedList;

public class MainActivity extends AppCompatActivity {

    private ListView m_ListView;//메모를 나열할 리스트 뷰
    private ArrayAdapter<String> m_Adapter; //리스트뷰에 쓰일 어댑터
    public ArrayList<String> nameOfFile= new ArrayList<String>();//파일명을 저장할 ArrayList
    private String strTitle=""; // 디렉토리 이름
    String sdPath = Environment.getExternalStorageDirectory().getAbsolutePath(); //안드로이드 내부 저장소 주소
    File file = new File(sdPath);




    private void CreateDirectory(String name){ // 폴더 생성하는 함수
        sdPath += name; // name 이라는 스트링에 적힌걸로 폴더 이름을 생성하게 하려고
       // file.mkdirs();
        if( !file.exists() ) {
            file.mkdirs();
            Toast.makeText(this, "Success", Toast.LENGTH_SHORT).show();
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
       /* File fList = new File(sdPath);
        File[] files = fList.listFiles();
        LinkedList<File> folderList = new LinkedList<File>();

        for(int i=0; i<files.length; i++){
            if(files[i].isDirectory()){
                folderList.add(files[i]);
            }
        }*/

////////////////////////////////////////////////찬혁이 소스
        // Android에서 제공하는 String 문자열 하나를 출력하는 layout으로 어댑터 생성
        m_Adapter = new ArrayAdapter<String>(this, R.layout.listview_items, nameOfFile);
        // Xml에서 추가한 ListView의 객체를 사용
        m_ListView = (ListView) findViewById(R.id.list);
        m_ListView.setAdapter(m_Adapter);
        // ListView 아이템 터치 시 이벤트를 처리할 리스너 설정
        m_ListView.setOnItemClickListener(onClickListItem);

        //리스트뷰 속성
        m_ListView.setOverScrollMode(View.OVER_SCROLL_IF_CONTENT_SCROLLS);//화면을 넘어가면 스크롤바 생성
        m_ListView.setDivider((new ColorDrawable(Color.GRAY)));//구분선 회색
        m_ListView.setDividerHeight(5);//구분선 굵기

        getTitleList();//폴더에 있는 텍스트파일의 이름을 받아와 ArrayList에 초기화

////////////////////////////////////////////////////

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() { /////// + 버튼 눌렀을 때
            @Override
            public void onClick(View view) {
                AlertDialog.Builder alert = new AlertDialog.Builder(MainActivity.this);

                alert.setTitle("Create Board");
                alert.setMessage("Wirte Board name");

                // Set an EditText view to get user input
                final EditText input = new EditText(MainActivity.this);
                alert.setView(input);

                alert.setPositiveButton("CREATE", new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int whichButton) {
                        String value = input.getText().toString();
                        value.toString();
                        // Do something with value!
                        CreateDirectory(value);
                        onResume();
                    }
                });


                alert.setNegativeButton("CANCLE",
                        new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int whichButton) {
                                // Canceled.
                            }
                        });

                alert.show();

            }
            });
    }

    //화면 회전 시 onCreate 호출 방지를 위한 설정
    @Override
    public void onConfigurationChanged(Configuration newConfig){
        super.onConfigurationChanged(newConfig);
    }
    @Override
    protected void onStart() {
        super.onStart();
    }
    //메인 액티비티로 복귀할 때 리스트뷰 업데이트를 위해 onResume()에 해당 코드를 삽입
    @Override
    protected void onResume() {
        //   Toast.makeText(getApplicationContext(),"onResume() Call.",Toast.LENGTH_SHORT).show();
        m_Adapter = new ArrayAdapter<String>(this, R.layout.listview_items, nameOfFile);
        // Xml에서 추가한 ListView의 객체를 사용
        m_ListView = (ListView) findViewById(R.id.list);
        m_ListView.setAdapter(m_Adapter);
        // ListView 아이템 터치 시 이벤트를 처리할 리스너 설정
        m_ListView.setOnItemClickListener(onClickListItem);
        getTitleList();//ArrayList을 현재 생성된 파일 목록에 맞추어 갱신
        super.onResume();
    }
    // 리스트 뷰 아이템 터치 이벤트 리스너 구현
    private AdapterView.OnItemClickListener onClickListItem = new AdapterView.OnItemClickListener() {

        @Override
        public void onItemClick(AdapterView<?> parent, View view, int position, long id) {//리스트 객체 터치 시, SeeMemoActivity 실행 및 인텐트 결과값 반환받음
          /*
            Intent intent = new Intent(MainActivity.this, SeeMemoActivity.class);
            intent.putExtra("show_title",m_Adapter.getItem(position));
            startActivityForResult(intent,2);
            */
        }
    };


    //ArrayList를 현재 파일 리스트에 맞게 갱신
    private String[] getTitleList(){
        try{
            FilenameFilter fileFilter = new FilenameFilter(){//확장자 필터
                public boolean accept(File dir, String name){
                    return name.endsWith(".txt"); //txt만 취급
                }
            };
            File file = new File("/data/data/com.example.administrator.mobiletermproject/files"); //메모 파일이 저장되는 경로
            File[] files = file.listFiles(fileFilter);//확장자 필터 적용
            String [] titleList = new String [files.length];//파일 갯수만큼 배열 생성

            //콘솔창에 현재 폴더에 있는 파일 출력 및 어레이리스트 업데이트
            System.out.println("@@@@@@@@@@ Text File List @@@@@@@@@@");
            System.out.println(">/data/data/com.example.administrator.mobiletermproject/files");
            nameOfFile.clear();//arraylist 초기화
            for(int i = 0;i < files.length;i++){//파일 갯수 만큼 돌면서 arraylist에 값 삽입
                titleList[i] = files[i].getName();
                nameOfFile.add(files[i].getName());
                System.out.println(i+" : "+files[i].getName());
            }
            return titleList;
        } catch( Exception e ){
            return null;
        }
    }









    @Override
    public boolean onCreateOptionsMenu(Menu menu) {

        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) { // 액션바 눌렀을 때 행동 여따 넣어야됨

        if(item.getItemId()== R.id.Search){//메모 생성 버튼 클릭시
            Intent intent = new Intent(MainActivity.this, LibraryActivity.class);
            startActivityForResult(intent,1);
        }


        return super.onOptionsItemSelected(item);
    }
}
