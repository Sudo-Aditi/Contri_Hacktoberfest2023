//BEST TIME TO BUY AND SELL STOCK
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int min_price = prices[0];
        int ans = 0;
        for(int i=1;i<prices.size();i++){
            ans = max(ans,prices[i]-min_price);
            min_price = min(min_price,prices[i]);
        }
        return ans;
    }
};

//BEST TIME TO BUY AND SELL STOCK2
class Solution {
public:
    int func(int ind,int buy,vector<int>& prices,vector<vector<int>> &dp){
        //base case
        if(ind==prices.size()){
            return 0;
        }
        if(dp[ind][buy]!=-1){
            return dp[ind][buy];
        }
        int profit=0;
        //here we'll check whether we can buy it or not and when we can sell it
        if(buy){  //means if buy is 1
            profit = max(-prices[ind]+func(ind+1,0,prices,dp),0+func(ind+1,1,prices,dp));
        }
        else{
            profit = max(prices[ind]+func(ind+1,1,prices,dp),0+func(ind+1,0,prices,dp));
        }
        return  dp[ind][buy] = profit;
    }
    int maxProfit(vector<int>& prices) {
        //we write a very good recursion concept here
        int buy=1;
        //memoization
        int n = prices.size();

        //for tabulation write base cases

        //now for space optimization
        vector<int> dp(2,0);
        for(int ind=n-1;ind>=0;ind--){
            vector<int> curr(2,0);
            for(int buy=0;buy<2;buy++){
                 int profit=0;
        //here we'll check whether we can buy it or not and when we can sell it
                if(buy){  //means if buy is 1
                    int case1 = -prices[ind];
                    int case2 = 0;
                    if(ind+1<n){
                        case1 += dp[0];
                        case2 = dp[1];
                    }
                    profit = max(case1,case2);
                }
                else{
                    int case1 = prices[ind];
                    int case2 = 0;
                    if(ind+1<n){
                        case1 += dp[1];
                        case2 = dp[0];
                    }
                    profit = max(case1,case2);
                }
                curr[buy] = profit;
            }
            dp=curr;
        }

        return dp[buy];
    }
};
//BEST TIME TO BUY AND SELL STOCK 3
int maxProfit(vector<int>& prices) {
        //ony the diff is here we will maintain a cap of two transcations
        int cap=2;
        int buy=1;
        int n = prices.size();
        //let's tabulatew
        vector<vector<vector<int>>> dp(n,vector<vector<int>>(2,vector<int>(3,0)));
        for(int ind=n-1;ind>=0;ind--){
            for(int buy=0;buy<2;buy++){
                for(int cap=2;cap>0;cap--){
                    int profit = 0;
                    if(buy){
                        int case1 = -prices[ind];
                        int case2=0;
                        if(ind+1<n){
                            case1 += dp[ind+1][0][cap];
                            case2 = dp[ind+1][1][cap];
                        }
                        profit = max(case1,case2);
                    }
                    else{
                        int case1 = prices[ind];
                        int case2=0;
                        if(ind+1<n){
                            case1 += dp[ind+1][1][cap-1];
                            case2 = dp[ind+1][0][cap];
                        }
                        profit = max(case1,case2);
                    }
                    dp[ind][buy][cap] = profit;
                }
            }
        }

        return dp[0][buy][cap]; 
    }
