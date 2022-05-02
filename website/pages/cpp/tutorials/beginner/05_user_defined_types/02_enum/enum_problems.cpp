// 1) no scoping - name conflicts
enum color { red, green, blue };
enum light { red, yellow, green }; // error: red and green already defined

// 2) no type safety
void set_traffic_light(light l);
color c = green;
set_traffic_light(c); // type mismatch but no error!
