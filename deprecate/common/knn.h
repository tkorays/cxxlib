#ifndef TK_KNN_H
#define TK_KNN_H


#include <vector>
#include <algorithm>
#include <functional>
#include "kvpair.h"
using namespace std;
using namespace tk;

namespace tk {
	// kvpair key(K) & value(V) type
	template <typename K,typename V> class knn {
	public:
		int k;
		vector<kvpair<K,V>> data;
		knn() { k = 0; }
		knn(int k_) {
			if (k<=0) {
				k = 0;
			}
			k = k_; 
		}
		void load_data(const vector<kvpair<K, V>> d) {
			data = d;
		}
		void load_data(const vector<K> keys, const vector<V> values) {
			size_t size = keys.size() < values.size() ? keys.size() : values.size();
			for (size_t i = 0; i < size; i++) {
				data.push_back(kvpair<K, V>(keys[i], values[i]));
			}
		}
		void clear_data() {
			data.clear();
		}
		void add_data(const kvpair<K, V> kvp) {
			data.push_back(kvp);
		}
		size_t data_size() { return data.size(); }
		K predict(const V val) {
			vector<kvpair<K, double>> key_dist;
			// calculate the distance
			for (size_t i = 0; i < data.size(); i++) {
				key_dist.push_back(kvpair<K, double>(data[i].key, data[i].value.distance(val)));
			}
			// sort by distance
			std::sort(key_dist.begin(), key_dist.end(), less<kvpair<K, double>>());
			// count the nearest point type
			vector<kvpair<K, int>> key_count;
			k = k < data_size() ? k : data_size();
			for (size_t i = 0; i < k; i++) {
				int index = index_in_vector(key_count, key_dist[i].key);
				if (index == -1) {
					key_count.push_back(kvpair<K, int>(key_dist[i].key, 1));
				} else {
					key_count[index].value = key_count[index].value+1;
				}
			}
			std::sort(key_count.begin(), key_count.end(), greater<kvpair<K, int>>());

			return key_count[0].key;
		}
	private:
		int index_in_vector(const vector<kvpair<K, int>> kvp, K key) {
			int index;
			for (index = 0; index < kvp.size(); index++) {
				if (kvp[index].key == key) {
					break;
				}
			}
			if (index == kvp.size()) {
				index = -1;
			}
			return index;
		}
	};
}



#endif // TK_KNN_H