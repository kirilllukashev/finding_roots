#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>

double EPS = 0.000000001;

int max_power;
double left, right;

double val(double root, std::vector<double> pol) {
    double ans = 0.0;
    double nw = 1;
    for (int ii = pol.size() - 1; ii > -1; --ii) {
        ans += pol[ii] * nw;
        nw *= root;
    }
    return ans;
}

double bin_f(double ll, double rr, std::vector<double> pol) {
    while (rr - ll > EPS) {
        double mm = ll + (rr - ll) / 2;
        if (val(ll, pol) * val(mm, pol) > 0) {
            ll = mm;
        } else {
            rr = mm;
        }
    }
    return (ll + rr) / 2;
}

std::vector<double> give_polynom(std::vector<double> pol) {
    std::vector <double> res;
    double len = pol.size();
    for (int ii = 0; ii < len - 1; ++ii) {
        res.push_back(pol[ii] * (len - 1 - ii));
    }
    return res;
}


std::vector <double> find_ans(std::vector <double> powers, double left, double right, int max_power) {
    if (powers.size() == 2) {
        std::vector <double> ans;
        double root = -powers[1] / powers[0];
        if (left <= root && root < right) {
            if (powers[1] == 0) {
                ans.push_back(0.0);
            } else {
                ans.push_back(root);
            }
        }

        return ans;
    }
    std::vector <double> extr = find_ans(give_polynom(powers), left, right, max_power - 1), root, point;
    point.push_back(left);
    for (int ii = 0; ii < extr.size(); ++ii) {
        point.push_back(extr[ii]);
    }
    point.push_back(right);
    for (int ii = 0; ii < point.size() - 1; ++ii) {
        if (fabs(val(point[ii], powers) - 0) < EPS) {
            root.push_back(point[ii]);
            if (ii != 0 && point[ii - 1] != point[ii]) {
                root.push_back(point[ii]);
            }
        }
    }
    for (int ii = 1; ii < point.size(); ++ii) {
        if (val(point[ii - 1], powers) * val(point[ii], powers) < 0) {
            double ans = bin_f(point[ii - 1], point[ii], powers);
            if (fabs(point[ii - 1] - ans) > sqrt(EPS) && fabs(point[ii] - ans) > sqrt(EPS)) {
                root.push_back(ans);
            }
        }
    }
    sort(root.begin(), root.end());
    return root;
}

int main() {
    std::cin >> max_power;
    std::vector<double> powers(max_power + 1);
    for (int ii = 0; ii < max_power + 1; ++ii) {
        std::cin >> powers[ii];
    }
    std::cin >> left >> right;
    std::vector<double> ans = find_ans(powers, left, right, max_power);
    for (int ii = 0; ii < ans.size(); ++ii) {
        std::cout << std::fixed << std::setprecision(6) << ans[ii] << " ";
    }
}
