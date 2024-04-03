#include <config/conf.h>
#include <foundation/sys/dbglog.h>
#include <periph/drivers/serial/uart_early.hpp>
#include <periph/gpio/gpio.hpp>
#include <isix.h>


namespace {
    constexpr auto led_0 = periph::gpio::num::PD13;
}

namespace app {
    // void test_thread(void*) {
    //     for(int i=0;;++i) {
    //         isix::wait_ms(500);
    //         if(i%2==0) {
    //             dbprintf("Loop %i",i>>1);
    //         }
    //         periph::gpio::set(led_0, i%2);
    //     }
    // }

    void print_array(int tab[], int tabLength){
    for(int i = 0; i < tabLength; ++i) {
        dbprintf("%d ", tab[i]);
    }
    dbprintf("\n");
    }


    void sort(int tab[], int tabLength){        
        int i, j;
        
        for (i = 0; i < tabLength-1; i++){   
            int jMin = i;
            for (j = i+1; j < tabLength; j++){
                if (tab[j] < tab[jMin]){
                    jMin = j;
                }
            }

            if (jMin != i) {
                int temp = tab[i];

                tab[i] = tab[jMin];
                tab[jMin] = temp;
            }
        }
    }

    void test_sort_function() {
        int tab[] = {9, 2, 5, 1, 7, 6, 8, 3, 4, 0};
        const int tabLength = sizeof(tab) / sizeof(tab[0]);

        dbprintf("Unsorted table:");
        print_array(tab, tabLength);

        sort(tab, tabLength);

        dbprintf("Sorted table:");
        print_array(tab, tabLength);
    }

    void test_thread(void*) {
        for(int i = 0; i < 10; ++i) { // Przykład: wykonaj sortowanie 10 razy
            test_sort_function();
            isix::wait_ms(500); // Odczekaj sekundę między testami
        }
    //     constexpr int tabLength = 10;
    //     int tab[tabLength];
    //     // Inicjalizacja generatora liczb losowych
    //     srand(time(nullptr));
    //     for(int n = 0; n < 50; ++n) { // Generuj i sortuj 50 razy
    //         // Generowanie nowej tablicy z losowymi danymi
    //         for(int i = 0; i < tabLength; ++i) {
    //             tab[i] = rand() % 100; // Liczby z zakresu 0-99
    //         }
    //         dbprintf("Tablica przed sortowaniem:");
    //         printArray(tab, tabLength);
    //         // Sortowanie tablicy
    //         sort(tab, tabLength);
    //         dbprintf("Tablica po sortowaniu:");
    //         printArray(tab, tabLength);
    //         // Czekaj 2 sekundy przed kolejnym cyklem
    //         isix::wait_ms(2000);
    //     }
    // }    
}
}


auto main() -> int
{
	// static isix::semaphore m_ulock_sem { 1, 1 };
    // isix::wait_ms( 500 );
	// dblog_init_locked(
	// 	[](int ch, void*) {
	// 		return periph::drivers::uart_early::putc(ch);
	// 	},
	// 	nullptr,
	// 	[]() {
	// 		m_ulock_sem.wait(ISIX_TIME_INFINITE);
	// 	},
	// 	[]() {
	// 		m_ulock_sem.signal();
	// 	},
	// 	periph::drivers::uart_early::open,
	// 	"serial0", 115200
	// );
    // Configure PD13 pin LED as an output
    // periph::gpio::setup( led_0,
    //     periph::gpio::mode::out{
    //         periph::gpio::outtype::pushpull,
    //         periph::gpio::speed::low
    //     }
    // );
	isix::task_create( app::test_thread, nullptr, 1536, isix::get_min_priority() );
    dbprintf("<<<< Hello STM32F411E-DISCO board >>>>");
	isix::start_scheduler();
	return 0;
}
