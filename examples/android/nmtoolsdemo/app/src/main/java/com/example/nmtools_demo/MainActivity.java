package com.example.nmtools_demo;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.view.View.OnClickListener;

public class MainActivity extends AppCompatActivity {

    EditText mStartEdit;
    EditText mStopEdit;
    EditText mStepEdit;
    TextView mTextView;

    private static final String TAG = "MyActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mStartEdit = (EditText)findViewById(R.id.startInput);
        mStopEdit  = (EditText)findViewById(R.id.stopInput);
        mStepEdit  = (EditText)findViewById(R.id.stepInput);
        mTextView = (TextView)findViewById(R.id.textView);

        mTextView.setText(random(new int[]{1,2,3}));

        Button clickButton = (Button) findViewById(R.id.button);
        clickButton.setOnClickListener((OnClickListener) v -> {
            try {
                int start = Integer.parseInt(mStartEdit.getText().toString());
                int stop  = Integer.parseInt(mStopEdit.getText().toString());
                int step  = Integer.parseInt(mStepEdit.getText().toString());
                mTextView.setText(arange(start,stop,step));
            } catch (Exception e) {
                Log.d(TAG, String.format("Exception: %s", e.toString()));
            }
        });
    }

    public native String  arange(int start, int stop, int step);
    public native String  random(int[] jshape);
    static {
        System.loadLibrary("nmtools-demo");
    }
}