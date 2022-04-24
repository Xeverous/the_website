if (typeid(a) == typeid(cat))
{
	auto& c = static_cast<cat&>(a);
}
