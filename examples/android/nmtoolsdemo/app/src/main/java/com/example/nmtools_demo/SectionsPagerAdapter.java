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
        } else {
            return new UfuncFragment();
        }
    }

    @Nullable
    @Override
    public CharSequence getPageTitle(int position) {
        if (position == 0) {
            return "arange";
        } else if (position == 1) {
            return "random";
        } else {
            return "ufunc";
        }
    }

    @Override
    public int getCount() {
        return 3;
    }
}
