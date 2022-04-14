class report { /* ... */ };
int compare(const report& lhs, const report& rhs);

bool operator==(const report& lhs, const report& rhs) { return compare(lhs, rhs) == 0; }
bool operator!=(const report& lhs, const report& rhs) { return compare(lhs, rhs) != 0; }
bool operator< (const report& lhs, const report& rhs) { return compare(lhs, rhs) <  0; }
bool operator> (const report& lhs, const report& rhs) { return compare(lhs, rhs) >  0; }
bool operator<=(const report& lhs, const report& rhs) { return compare(lhs, rhs) <= 0; }
bool operator>=(const report& lhs, const report& rhs) { return compare(lhs, rhs) >= 0; }
