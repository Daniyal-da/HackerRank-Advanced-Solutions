#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Spell { 
    string scrollName;
public:
    Spell(string name) : scrollName(name) {}
    /*
    مخرب باید virtual باشه تاdynamic_cast کار بکنه
    چون dynamic_cast فقط روی کلاس polymorphic کار میکنه 
    */
    virtual ~Spell() {}
    string revealScrollName() { return scrollName; }
};

class Fireball : public Spell { 
    int power;
public:
    Fireball(int p) : Spell("Fireball"), power(p) {}
    void revealFirepower() { cout << "Fireball: " << power << endl; }
};

class Frostbite : public Spell {
    int power;
public:
    Frostbite(int p) : Spell("Frostbite"), power(p) {}
    void revealFrostpower() { cout << "Frostbite: " << power << endl; }
};

class Thunderstorm : public Spell { 
    int power;
public:
    Thunderstorm(int p) : Spell("Thunderstorm"), power(p) {}
    void revealThunderpower() { cout << "Thunderstorm: " << power << endl; }
};

class Waterbolt : public Spell { 
    int power;
public:
    Waterbolt(int p) : Spell("Waterbolt"), power(p) {}
    void revealWaterpower() { cout << "Waterbolt: " << power << endl; }
};

class SpellJournal {
public:
    static string journal;
    static string read() { return journal; }
};
string SpellJournal::journal = "";


void counterspell(Spell *spell) {
    // 1. چک کردن نوع اسپل با استفاده از dynamic_cast
    if (Fireball *f = dynamic_cast<Fireball*>(spell)) {
        f->revealFirepower();
    }
    else if (Frostbite *f = dynamic_cast<Frostbite*>(spell)) {
        f->revealFrostpower();
    }
    else if (Thunderstorm *t = dynamic_cast<Thunderstorm*>(spell)) {
        t->revealThunderpower();
    }
    else if (Waterbolt *w = dynamic_cast<Waterbolt*>(spell)) {
        w->revealWaterpower();
    }
    else {
        // 2. الگوریتم LCS (Longest Common Subsequence)
        // وقتی اسپل عمومی است، باید بیشترین حروف مشترک بین طومار و ژورنال را پیدا کنیم
        string s1 = spell->revealScrollName();
        string s2 = SpellJournal::journal;
        int m = s1.length();
        int n = s2.length();

        // ساخت جدول DP
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                if (i == 0 || j == 0)
                    dp[i][j] = 0;
                else if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        cout << dp[m][n] << endl;
    }
}


int main() {
    
    SpellJournal::journal = "VOLTA";
    Spell* s1 = new Fireball(10);
    Spell* s2 = new Spell("VOLDEMORT"); // اسپلی که باید با LCS حل شود

    counterspell(s1); //10
    counterspell(s2); // خروجی باید طول مشترک VOL بین VOLTA و VOLDEMORT باشد که ۳ است
    return 0;
}