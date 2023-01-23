package com.example.nmtools_demo;

import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;

import android.util.Log;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.view.View.OnClickListener;

public class ArangeFragment extends Fragment {

    public static ArangeFragment newInstance() {
        ArangeFragment fragment = new ArangeFragment();
        return fragment;
    }

    private static final String TAG = "ArangeFragment";

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.arange_fragment, container, false);
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {
        Button clickButton  = (Button)   getView().findViewById(R.id.arangeButton);

        clickButton.setOnClickListener((OnClickListener) v->{
            EditText mStartEdit = (EditText) getView().findViewById(R.id.startTextEdit);
            EditText mStopEdit  = (EditText) getView().findViewById(R.id.stopTextEdit);
            EditText mStepEdit  = (EditText) getView().findViewById(R.id.stepTextEdit);
            TextView textView  = (TextView) getView().getRootView().findViewById(R.id.textView);
            try {
                // arange
                int start = Integer.parseInt(mStartEdit.getText().toString());
                int stop  = Integer.parseInt(mStopEdit.getText().toString());
                int step  = Integer.parseInt(mStepEdit.getText().toString());

                NmTools.NDArrayFloat array = NmTools.arange(start,stop,step);

                textView.setText(array.to_string());
            } catch (Exception e) {
                Log.d(TAG, String.format("Exception: %s", e.toString()));
            }
        });
    }
}