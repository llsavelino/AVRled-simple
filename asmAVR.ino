void setup(void);     void loop(void);
extern "C"  { void __asmFunc(void); };

auto main(int argc, const char **argv) 
->                      decltype(0x00) 
{
    DDRD  |=              (0b1 << PD7); 
    PORTD &=             ~(0b1 << PD7);
    setup                           ();
    return                        0x00;
};

inline auto                  setup(void) 
-> void {         __asmFunc();        };
inline auto loop                  (void) 
-> void {/*\@$@$@$@$@$@$@$@$@$@$@$@$\*/};