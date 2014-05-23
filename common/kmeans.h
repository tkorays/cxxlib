#ifndef TK_KMEANS_H
#define TK_KMEANS_H

#include <vector>
#include <algorithm>
#include <functional>
#include "kvpair.h"

using namespace std;
namespace tk {

	template <typename T> class kmeans {
	public:
		int k;
		vector<T> data;

		kmeans() { k = 0; }
		kmeans(int k_) { k = k_; }
		void load_data(const vector<T> dt) { data = dt; }
		void add_data(T d) { data.push_back(d); }
		void clear_data() { data.clear(); }
		size_t data_size() { return data.size(); }

		vector<kvpair<T, vector<T>>> clustering(vector<T> center) {
			if (center.size()<k) {
				k = center.size();
			}
			vector<kvpair<T, vector<T>>> result;
			// init
			for (size_t i = 0; i < k; i++) {
				result.push_back(kvpair<T, vector<T>>(center[i], vector<T>()));
			}
			bool flag = false;
			if (!flag) {
				flag = true;
				for (size_t i = 0; i < data_size(); i++) {
					vector<kvpair<T, double>> dst_center;
					// for every center
					for (size_t j = 0; j < k; j++) {
						dst_center.push_back(kvpair<T,double>(result[j].key, result[j].key.distance(data[i])));
					}
					std::sort(dst_center.begin(), dst_center.end(), less<kvpair<T, double>>());
					int index = index_in_vector(result, dst_center[0].key);
					result[index].value.push_back(data[i]);
				}
				// refresh center point
				for (size_t i = 0; i < result.size(); i++) {
					T t;
					for (size_t j = 0; j < result[i].value.size(); j++) {
						t = t + result[i].value[j];
					}
					t = t / result[i].value.size();
					if (!(result[i].key == t)) {
						flag = false;
					}
					result[i].key = t;
				}
				if (flag) {
					for (size_t i = 0; i < result.size(); i++) {
						result[i].value.clear();
					}
				}
			}
			
			return result;
		}
	private:
		int index_in_vector(vector<kvpair<T, vector<T>>> r, T t) {
			int index;
			for (index = 0; index < r.size(); index++) {
				if (r[index].key == t) {
					break;
				}
			}
			if (index == r.size()) {
				index = -1;
			}
			return index;
		}

	};
}

#endif // TK_KMEANS_H