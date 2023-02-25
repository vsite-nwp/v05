#### vježba 5

Napišite program za crtanje razlomljenih linija (_polyline_). 
* klik lijevom tipkom miša dodaje novu točku
* pritisak na _Backspace_ izbacuje zadnju dodanu točku (_undo_)
* pritisak na _Esc_ briše prozor

Uputstva:
* dodajte u baznu klasu `vsite::nwp::window` obradu poruke `WM_PAINT`
* točke možete držati u listi (`std::list<POINT>`)
* na klik dodajete točku u listu (i invalidirate prozor) – `push_back`
* na `on_paint` iterirate kroz listu
* za crtanje razlomljene linije koristite [MoveToEx](https://msdn.microsoft.com/en-us/library/dd145069%28v=vs.85%29.aspx) (jednom) i [LineTo](https://msdn.microsoft.com/en-us/library/dd145029%28v=vs.85%29.aspx)
* na pritisnutu tipku _Backspace_ izbacite zadnju točku (i invalidirate prozor) – `pop_back`
* na pritisnutu tipku _Esc_ praznite listu (i invalidirate prozor)

![drawing](/screenshot.jpg?raw=true)
