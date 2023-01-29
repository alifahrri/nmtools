package com.example.nmtools_demo;

import android.content.Context;

import androidx.annotation.Nullable;
import androidx.annotation.StringRes;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentPagerAdapter;

import com.example.nmtools_demo.R;

public class SectionsPagerAdapter extends FragmentPagerAdapter {

    private final Context mContext;

    public SectionsPagerAdapter(Context context, FragmentManager fm) {
        super(fm);
        mContext = context;
    }

    @Override
    public Fragment getItem(int position) {
        if (position == 0) {
            return new ArangeFragment();
        } else if (position == 1) {
            return new RandomFragment();
        } else if (position == 2) {
            return new UfuncFragment();
        } else if (position == 3) {
            return new Ufunc2Fragment();
        } else {
            return new ReduceFragment();
        }
    }

    @Nullable
    @Override
    public CharSequence getPageTitle(int position) {
        if (position == 0) {
            return "arange";
        } else if (position == 1) {
            return "random";
        } else if (position == 2) {
            return "ufunc";
        } else if (position == 3) {
            return "ufunc (2)";
        } else {
            return "reduce";
        }
    }

    @Override
    public int getCount() {
        return 5;
    }
}
