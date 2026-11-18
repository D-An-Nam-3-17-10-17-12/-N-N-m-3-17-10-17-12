#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

bool laSo(const string& s) {
	if (s.empty()) return false;
	for (char ch : s)
		if (ch < '0' || ch>'9') return false;
	return true;
}
bool qtyHopLe(const string& s, long long& out) {
	if (!laSo(s) || s.size() > 10) return false;
	out = stoll(s);
	return out >= 1 && out <= 1000000000LL;
}
int main() {

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int Q;
	cin >> Q;
	cin.ignore();

	unordered_map<string, queue<pair<string, long long>>> hangDoi;
	unordered_map<string, long long> tongTK;
	unordered_set<string> maUsed;
	for (int t = 0;t < Q;t++) {
		string line;
		getline(cin, line);
		stringstream ss(line);
		vector<string> tokens;
		string tok;

		while (ss >> tok) tokens.push_back(tok);
		if (tokens.empty()) {
			cout << "INVALID\n";
			continue;
		}
		// Xử lý IMPORT
		if (tokens[0] == "IMPORT") {
			long long qty;
			if (tokens.size() != 4 || tokens[1].size() > 20 || tokens[2].size() > 20 || !qtyHopLe(tokens[3], qty)) {
				cout << "INVALID\n";
				continue;
			}
			string sku = tokens[1];
			string lot = tokens[2];

			if (maUsed.count(lot))
				cout << "DUPLICATE_LOT\n";
			else {
				maUsed.insert(lot);
				hangDoi[sku].push({ lot,qty });
				tongTK[sku] += qty;
				cout << "OK\n";
			}
		}
		// Xử lý STOCK
		else if (tokens[0] == "STOCK") {
			if (tokens.size() != 2 || tokens[1].size() > 20) {
				cout << "INVALID\n";
				continue;
			}
			string sku = tokens[1];
			auto it = tongTK.find(sku);
			if (it != tongTK.end())
				cout << it->second << "\n";
			else
				cout << 0 << "\n";
		}
		// Xử lý EXPORT
		else if (tokens[0] == "EXPORT") {
			long long qty;
			if (tokens.size() != 3 || tokens[1].size() > 20 || !qtyHopLe(tokens[2], qty)) {
				cout << "INVALID\n";
				continue;
			}
			string sku = tokens[1];

			auto it = tongTK.find(sku);
			long long stock = (it == tongTK.end()) ? 0 : it->second;

			if (stock < qty)
				cout << "NOT_ENOUGH " << stock << "\n";
			else {
				auto& q = hangDoi[sku];
				long long remaining = qty;
				string result = "";
				while (remaining > 0) {
					auto& lot = q.front();
					long long take = min(lot.second, remaining);
					if (!result.empty()) result += " ";
					result += lot.first + ":" + to_string(take);

					lot.second -= take;
					remaining -= take;

					if (lot.second == 0)
						q.pop();
				}
				it->second -= qty;
				cout << result << "\n";
			}
		}
		else
			cout << "INVALID\n";
	}
	return 0;
}