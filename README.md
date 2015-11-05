#### vježba 5

Napišite program za crtanje razlomljenih linija (polyline). 
* klik lijevom tipkom miša dodaje novu točku
* pritisak na Backspace izbacuje zadnju dodanu točku (undo)
* pritisak na Esc briše prozor

Uputstva:
* dodajte u baznu klasu Window obradu poruke WM_PAINT
* točke možete držati u listi (std::list<POINT>)
* na klik dodajete točku u listu (i invalidirate prozor) – push_back
* na OnPaint iterirate kroz listu
* za crtanje razlomljene linije koristite [MoveToEx](https://msdn.microsoft.com/en-us/library/dd145069%28v=vs.85%29.aspx) (jednom) i [LineTo](https://msdn.microsoft.com/en-us/library/dd145029%28v=vs.85%29.aspx)
* na pritisnutu tipku Backspace izbacite zadnju točku (i invalidirate prozor) – pop_back
* na pritisnutu tipku Esc praznite listu (i invalidirate prozor)

![drawing](/screenshot.jpg?raw=true)
