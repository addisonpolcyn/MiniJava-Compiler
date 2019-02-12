// This sample contains a little bit more syntax usage than Factorial
// - List of statements in a block
// - Assignment operations
// - Function calls with multiple arguments
class HanoiDemo {
	public static void main (String [] argv) {
		{
			// Statements
			// `dummy` is a variable.
			// It is not declared but the syntax parser doesn't care about that.
			// In this way the program can survive parsing.
			dummy = new Hanoi().start(8);

			/* The class `Numbers` is in the second sample code
			 * This also poses no syntax errors but is semantically incorrect
			 */
			System.out.println(new Numbers().choose(10, 5));
		}
	}
}
