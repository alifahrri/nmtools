package com.example.nmtools_demo;

import androidx.lifecycle.ViewModelProvider;

import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import android.util.Log;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.view.View.OnClickListener;

import com.example.nmtools_demo.NmTools;

public class RandomFragment extends Fragment {

    private BlankViewModel mViewModel;

    private static final String TAG = "RandomFragment";

    public static RandomFragment newInstance() {
        return new RandomFragment();
    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        return inflater.inflate(R.layout.random_fragment, container, false);
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {

        Button clickButton = (Button)   getView().findViewById(R.id.randomButton);
        EditText shapeEdit = (EditText) getView().findViewById(R.id.shapeInputText);

        clickButton.setOnClickListener((OnClickListener) v -> {
            TextView textView  = (TextView) getView().getRootView().findViewById(R.id.textView);
            try {
                // random
                String shape_str = shapeEdit.getText().toString();
                String[] dims_str = shape_str.split(",");
                int[] shape = new int[dims_str.length];
                for (int i=0; i<shape.length; i++) {
                    shape[i] = Integer.parseInt(dims_str[i]);
                }
                String random = NmTools.random(-1.0f, 1.0f, shape);
                Log.d(TAG, random);
                textView.setText(random);
            } catch (Exception e) {
                Log.d(TAG, String.format("Exception: %s", e.toString()));
            }
        });
    }

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        mViewModel = new ViewModelProvider(this).get(BlankViewModel.class);
        // TODO: Use the ViewModel
    }

}