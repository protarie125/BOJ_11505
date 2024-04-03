#include <algorithm>
#include <bit>
#include <chrono>
#include <cmath>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

using vb = vector<bool>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<double>;
using vii = vector<pii>;
using vll = vector<pll>;
using vs = vector<string>;

using vvb = vector<vb>;
using vvi = vector<vi>;
using vvl = vector<vl>;
using vvd = vector<vd>;

const auto kMod = 1000000007LL;
const auto kDefault = 1LL;

ll n, m, k;
ll sz;
vl A;
vl Tree;

ll Le(ll k) {
  return 2 * k;
}
ll Ri(ll k) {
  return 2 * k + 1;
}

void Set(ll idx, ll x) {
  idx += sz;
  Tree[idx] = x;
  while (0 < idx) {
    idx /= 2;
    Tree[idx] = (Tree[Le(idx)] * Tree[Ri(idx)]) % kMod;
  }
}
ll Query(ll k, ll b, ll e, ll l, ll r) {
  if (e <= b || e <= l || r <= b) {
    return kDefault;
  }

  if (l <= b && e <= r) {
    return Tree[k];
  }

  const auto& mid = (b + e) / 2;
  return (Query(Le(k), b, mid, l, r) * Query(Ri(k), mid, e, l, r)) % kMod;
}

void Print() {
  auto p = 1LL;
  auto w = 1LL;
  auto u = sz;
  while (p < 2 * sz) {
    for (auto i = 0; i < w; ++i) {
      auto oss = ostringstream{};
      oss << "| " << Tree[p + i] << " ";
      cout << setw(u * 8) << left << oss.str();
    }
    cout << '\n';

    p += w;
    w *= 2;
    u /= 2;
  }
}

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  cin >> n >> m >> k;

  sz = 1;
  while (sz < n) {
    sz *= 2;
  }

  A = vl(sz, kDefault);
  for (auto i = 0; i < n; ++i) {
    cin >> A[i];
  }

  Tree = vl(2 * sz, kDefault);
  for (auto i = 0; i < n; ++i) {
    Set(i, A[i]);
  }
  // Print();

  for (auto j = 0LL; j < (m + k); ++j) {
    ll q;
    cin >> q;
    if (1 == q) {
      ll idx, x;
      cin >> idx >> x;
      --idx;
      Set(idx, x);
      // Print();
    } else if (2 == q) {
      ll l, r;
      cin >> l >> r;
      --l;
      cout << Query(1, 0, sz, l, r) << '\n';
    }
  }

  return 0;
}
