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
import android.widget.EditText;
import android.widget.TextView;
import android.view.View.OnClickListener;

import com.example.nmtools_demo.NmTools;

/**
 * A simple {@link Fragment} subclass.
 * Use the {@link Ufunc2Fragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class Ufunc2Fragment extends Fragment {

    private static final String TAG = "Ufunc2Fragment";

    public Ufunc2Fragment() {
        // Required empty public constructor
    }

    /**
     * Use this factory method to create a new instance of
     * this fragment using the provided parameters.
     *
     * @param param1 Parameter 1.
     * @param param2 Parameter 2.
     * @return A new instance of fragment Ufunc2Fragment.
     */
    // TODO: Rename and change types and number of parameters
    public static Ufunc2Fragment newInstance(String param1, String param2) {
        Ufunc2Fragment fragment = new Ufunc2Fragment();
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
        return inflater.inflate(R.layout.fragment_ufunc2, container, false);
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {
        Button clickButton = (Button) getView().findViewById(R.id.buttonUfunc2Apply);
        EditText lhsShapeText = (EditText) getView().findViewById(R.id.editTextUfunc2LhsShape);
        EditText rhsShapeText = (EditText) getView().findViewById(R.id.editTextUfunc2RhsShape);

        RadioButton addBtn = (RadioButton) getView().findViewById(R.id.radioButtonUfunc2Add);
        RadioButton subBtn = (RadioButton) getView().findViewById(R.id.radioButtonUfunc2Subtract);
        RadioButton mulBtn = (RadioButton) getView().findViewById(R.id.radioButtonUfunc2Multiply);

        clickButton.setOnClickListener((OnClickListener) v -> {
            TextView textView = (TextView) getView().getRootView().findViewById(R.id.textView);

            try {
                String lhs_shape_str = lhsShapeText.getText().toString();
                String rhs_shape_str = rhsShapeText.getText().toString();

                int[] lhs_shape = NmTools.parse_shape(lhs_shape_str);
                int[] rhs_shape = NmTools.parse_shape(rhs_shape_str);

                NmTools.NDArrayFloat lhs_array = NmTools.random(-1.0f,1.0f,lhs_shape);
                NmTools.NDArrayFloat rhs_array = NmTools.random(-1.0f,1.0f,rhs_shape);

                NmTools.NDArrayFloat result;
                if (addBtn.isChecked()) {
                    result = NmTools.add(lhs_array,rhs_array);
                } else if (subBtn.isChecked()) {
                    result = NmTools.subtract(lhs_array,rhs_array);
                } else {
                    result = NmTools.multiply(lhs_array,rhs_array);
                    mulBtn.setChecked(true);
                }

                String lhs_str = lhs_array.to_string();
                String rhs_str = rhs_array.to_string();
                String res_str = result.to_string();

                Log.d(TAG, lhs_str);
                Log.d(TAG, rhs_str);
                Log.d(TAG, res_str);
                textView.setText(String.format("LHS:\n%s\nRHS:%s\n\nBinary Ufunc Result:\n%s",lhs_str,rhs_str,res_str));
            } catch (Exception e) {
                Log.d(TAG, String.format("Exception: %s", e.toString()));
            }
        });
    }
}