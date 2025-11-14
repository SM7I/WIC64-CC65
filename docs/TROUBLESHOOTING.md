1. Compiler Errors (cc65)
-------------------------

*** “Too many local variables”
Cause: cc65 has a strict limit on locals per function (≈10–12).

Fix:

Move large arrays (e.g., char temp[256]) to global static scope.

Declare all variables at the top of the function, not inline.

Reduce locals by reusing variables across steps.

*** “Undefined symbol”
Cause: Function prototypes missing in headers.

Fix:

Ensure every function is declared in its .h file.

Example: Add uint8_t peek(uint16_t addr); to wic64lib.h.

*** “Constant is long” warning
Cause: cc65 treats 0xFFFF as a 32‑bit constant.

Fix:

Cast explicitly: (uint16_t)0xFFFF

Or use 65535u which cc65 accepts as 16‑bit unsigned.

*** “Statement has no effect”
Cause: Usually from a typo or missing semicolon.

Fix:

Double‑check variable names and ensure all statements end with ;.

2. Runtime Issues
-----------------

*** WiC64 not responding
Cause: CIA2 ports not configured correctly.

Fix:

Call wic_port_send_setup() before sending.

Call wic_port_recv_setup() before reading.

*** Garbage characters in URL
Cause: PETSCII vs ASCII mismatch.

Fix:

Use ascii_to_petscii() before sending URLs.

Ensure strings are null‑terminated.

*** Buffer overflow
Cause: Response larger than buffer.

Fix:

Always pass buffer size to wic_get_url.

Check return value and cap copy length.

*** Timeouts / hangs
Cause: Waiting for CIA2 interrupt flag that never arrives.

Fix:

Add timeout logic in wic_com loop.

Return WIC_TIMEOUT if flag not set after N iterations.

3. Debugging Tips
-----------------

*** Using VICE Monitor
Watch $DD01 (PRB) for data bytes.

Watch $DD0D (ICR) for interrupt flags.

Example:

(VICE) break $dd01
(VICE) break $dd0d
Check memory writes
Use peek() and poke() to verify data at target addresses.

Example:

cprintf("Byte at $0801: %u\n", peek(0x0801));

4. Best Practices
-----------------

Keep URLs short (<255 chars) to fit static buffer.

Use wic_send_command() for simple commands, wic_post_data() for POSTs.

Always clear interrupts with wic_irq_clear() after POST.

Test with small payloads before scaling up.
