enum class color { red, green, blue };
enum class light { red, yellow, green }; // color::red and light::red do not conflict

void set_traffic_light(light l);
color c = green;        // error: no "green" in current scope
color c = color::green; // ok
auto c = color::green;  // ok, now even better
set_traffic_light(c);   // error: parameter 1 expects light but got color
