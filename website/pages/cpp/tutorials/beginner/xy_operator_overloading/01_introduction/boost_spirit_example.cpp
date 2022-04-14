// example using third edition of the library
namespace x3 = boost::spirit::x3;

// # followed by any number of (any character except end-of-line) followed by (end-of-line or end-of-input)
const auto directive           = '#'  > *(x3::char_ - x3::eol) > (x3::eol | x3::eoi);

const auto single_line_comment = "//" > *(x3::char_ - x3::eol) > (x3::eol | x3::eoi);
const auto multi_line_comment  = "/*" > *(x3::char_ - "*/") > "*/";
const auto comment = single_line_comment | multi_line_comment;
