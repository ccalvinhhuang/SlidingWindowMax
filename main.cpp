#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> maxSlidingWindow(vector<int>& nums, int k){
    int f[nums.size()/k + 1][k];
    int b[nums.size()/k + 1][k];
    for(int i = 0; i < nums.size()/k + 1; i++){
        int loop_amt = k;
        if(i == nums.size() / k) loop_amt = nums.size() % k;
        for(int j = 0; j < loop_amt; j++){
            if(j == 0){
                f[i][j] = nums[k * i + j];
                if(i == nums.size() / k){
                    b[i][nums.size() % k - j - 1] = nums[k * i + nums.size() % k - 1];
                    continue;
                }
                b[i][k - j - 1] = nums[k * i + k - 1];
            }
            else{
                f[i][j] = max(nums[k * i + j], f[i][j - 1]);
                if(i == nums.size() / k){
                    b[i][nums.size() % k - j - 1] = max(nums[k * i + (nums.size() % k - (j + 1))], b[i][nums.size() % k - j]);
                    continue;
                }
                b[i][k - j - 1] = max(nums[k * i + k - (j + 1)], b[i][k - j]);
            }
        }
    }
    int l_x = 0, l_y = 0;
    int r_x = k - 1, r_y = 0;
    vector<int> ans;
    for(int i = k - 1; i < nums.size(); i++){
        if(l_y == r_y){
            ans.push_back(f[l_y][r_x]);
        }
        else{
            int to_push = max(f[r_y][r_x], b[l_y][l_x]);
            ans.push_back(to_push);
        }
        if(r_x == k - 1){
            r_y++;
            r_x = 0;
        }
        else{
            r_x++;
        }
        if(l_x == k - 1){
            l_y++;
            l_x = 0;
        }
        else{
            l_x++;
        }
    }
    return ans;
}

