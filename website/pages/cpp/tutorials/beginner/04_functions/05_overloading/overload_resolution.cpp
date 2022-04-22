void f1(int, float);  // A
void f1(int, double); // B
void f1(long, float); // C

// error: ambiguous call
// A: requires 2x narrowing convertion (long => int, double => float)
// B: requires 1x narrowing convertion (long => int)
// C: requires 1x narrowing convertion (double => float)
f1(42l, 3.14);

void f2(unsigned); // X
void f2(double);   // Y

// error: ambiguous call
// X: requires 1x narrowing (int => unsigned)
// Y: requires 1x narrowing (int => double)
f2(0);

// ok: perfect match with X
f2(0u);

// ok: selects Y
// X: requires 1x narrowing (float => unsigned)
// Y: requires 1x promotion (float => double)
f2(3.14f);

// error: ambiguous call
// X: requires 1x narrowing (char => unsigned)
// Y: requires 1x narrowing (char => double)
f2('a');
