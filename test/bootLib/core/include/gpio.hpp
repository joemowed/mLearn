namespace GPIO {
enum class MODE { OUTPUT, AF, INPUT, ANALOG };
enum class SPEED { LOW, MEDIUM, HIGH, VERY_HIGH };

//"FLOATING" is open drain for the output
enum class RESISTOR { FLOATING, PULL_DOWN, PULL_UP };

} // namespace GPIO
