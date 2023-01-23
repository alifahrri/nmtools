package com.example.nmtools_demo;

import android.os.Bundle;

import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProvider;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import android.util.Log;
import android.widget.Button;
import android.widget.RadioButton;
import android.widget.EditText;
import android.widget.TextView;
import android.view.View.OnClickListener;

import com.example.nmtools_demo.NmTools;

/**
 * A simple {@link Fragment} subclass.
 * Use the {@link UfuncFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class UfuncFragment extends Fragment {

    private static final String TAG = "UfuncFragment";

    public UfuncFragment() {
        // Required empty public constructor
    }

    /**
     * Use this factory method to create a new instance of
     * this fragment using the provided parameters.
     *
     * @param param1 Parameter 1.
     * @param param2 Parameter 2.
     * @return A new instance of fragment UfuncFragment.
     */
    // TODO: Rename and change types and number of parameters
    public static UfuncFragment newInstance() {
        return new UfuncFragment();
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.fragment_ufunc, container, false);
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {
        Button clickButton = (Button) getView().findViewById(R.id.ufuncApplyButton);
        EditText shapeText = (EditText) getView().findViewById(R.id.ufuncTextEdit);

        RadioButton reluBtn = (RadioButton) getView().findViewById(R.id.ufuncReluRadioBtn);
        RadioButton sigmoidBtn = (RadioButton) getView().findViewById(R.id.ufuncSigmoidRadioBtn);
        RadioButton sinBtn = (RadioButton) getView().findViewById(R.id.ufuncSinRadioBtn);

        clickButton.setOnClickListener((OnClickListener) v -> {
            TextView textView = (TextView) getView().getRootView().findViewById(R.id.textView);
            try {
                String shape_str = shapeText.getText().toString();
                int[] shape = NmTools.parse_shape(shape_str);
                NmTools.NDArrayFloat random = NmTools.random(-1.0f,1.0f,shape);
                NmTools.NDArrayFloat result;
                if (reluBtn.isChecked()) {
                    result = NmTools.relu(random);
                } else if (sigmoidBtn.isChecked()) {
                    result = NmTools.sigmoid(random);
                } else {
                    result = NmTools.sin(random);
                    sinBtn.setChecked(true);
                }
                String random_str = random.to_string();
                String result_str = result.to_string();
                Log.d(TAG, random_str);
                Log.d(TAG, result_str);
                textView.setText(String.format("Original:\n%s\n\nUfunc result:\n%s",random_str,result_str));
            } catch (Exception e) {
                Log.d(TAG, String.format("Exception: %s", e.toString()));
            }
        });
    }
}