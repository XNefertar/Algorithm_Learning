class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int total_tank = 0, cur_tank = 0, start = 0;
        
        for (int i = 0; i < gas.size(); i++) {
            int remain = gas[i] - cost[i];
            total_tank += remain;
            cur_tank += remain;
            
            // When the current remaining fuel is less than 0, it means that no position 
            // in the range [start, i] can complete the entire journey.
            // Why?
            // Suppose there exists a position k within the range [start, i] that can complete the journey.
            // Since position k can complete the journey, the remaining fuel at any position along the way must be greater than 0. 
            // This means that the fuel level from [k, i] must be positive.
            // However, according to the assumption, the total remaining fuel in [start, i] is less than 0, 
            // so the total fuel in [start, k] must be negative.
            // This means [start, k] forms a new invalid range.
            // Since the loop starts from i = 0, it is impossible for the calculation to have covered [start, i] 
            // without also covering [start, k] earlier.
            // This contradicts the problem statement, proving that no k in [start, i] can complete the journey.
            // Thus, the global correctness of the greedy algorithm is established.
            if (cur_tank < 0) {
                start = i + 1;
                cur_tank = 0; 
            }
        }
        
        return total_tank >= 0 ? start : -1;
    }
};