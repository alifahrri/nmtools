package com.example.nmtools_demo;

import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import android.util.Log;
import android.widget.Button;
import android.widget.RadioButton;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.TextView;
import android.view.View.OnClickListener;

import com.example.nmtools_demo.NmTools;

/**
 * A simple {@link Fragment} subclass.
 * Use the {@link ReduceFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class ReduceFragment extends Fragment {

    private static final String TAG = "ReduceFragment";

    public ReduceFragment() {
        // Required empty public constructor
    }

    /**
     * Use this factory method to create a new instance of
     * this fragment using the provided parameters.
     *
     * @param param1 Parameter 1.
     * @param param2 Parameter 2.
     * @return A new instance of fragment ReduceFragment.
     */
    // TODO: Rename and change types and number of parameters
    public static ReduceFragment newInstance(String param1, String param2) {
        ReduceFragment fragment = new ReduceFragment();
        return fragment;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.fragment_reduce, container, false);
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstance) {
        Button clickButton = (Button) getView().findViewById(R.id.buttonReduceApply);
        EditText shapeText = (EditText) getView().findViewById(R.id.editTextReduceShape);
        EditText axisText  = (EditText) getView().findViewById(R.id.editTextReduceAxis);

        RadioButton addBtn = (RadioButton) getView().findViewById(R.id.radioButtonReduceAdd);
        RadioButton mulBtn = (RadioButton) getView().findViewById(R.id.radioButtonReduceMultiply);

        CheckBox keepdimsBox = (CheckBox) getView().findViewById(R.id.checkBoxReduceKeepdims);

        clickButton.setOnClickListener((OnClickListener) v -> {
           TextView textView = (TextView) getView().getRootView().findViewById(R.id.textView);

           try {
               String shape_str = shapeText.getText().toString();
               String axis_str  = axisText.getText().toString();

               int[] shape = NmTools.parse_shape(shape_str);
               int[] axis  = NmTools.parse_shape(axis_str);
               boolean keepdims = keepdimsBox.isChecked();

               NmTools.NDArrayFloat array = NmTools.random(-1.0f,1.0f,shape);

               NmTools.NDArrayFloat result;
               if (addBtn.isChecked()) {
                   result = NmTools.reduce_add(array,axis,keepdims);
               } else {
                   result = NmTools.reduce_multiply(array,axis,keepdims);
                   mulBtn.setChecked(true);
               }

               String array_str = array.to_string();
               String result_str = result.to_string();

               textView.setText(String.format("Original:\n%s\n\nResult:\n%s",array_str,result_str));
           } catch (Exception e) {
               Log.d(TAG, String.format("Exception: %s", e.toString()));
           }
        });
    }
}