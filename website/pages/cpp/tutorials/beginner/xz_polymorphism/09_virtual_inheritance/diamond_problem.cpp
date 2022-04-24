class animal { /* functionality common for all animals... */ };

class mammal: public animal { /* functionality common for all mammals... */ };
class flying: public animal { /* functionality common for all flying creatures... */ };

// bat indirectly inherits animal twice
class bat: public mammal, public flying { /* ... */ };
