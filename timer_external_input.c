// #define F_CPU 16000000UL
// #include <avr/io.h>
// #include <util/delay.h>
// #include <stdint.h>
// 
// static const uint8_t Font[18] = {
// 	0x3F, 0x06, 0x5B, 0x4F, // 0,1,2,3
// 	0x66, 0x6D, 0x7C, 0x07, // 4,5,6,7
// 	0x7F, 0x67, 0x77, 0x7C, // 8,9,A,b
// 	0x39, 0x5E, 0x79, 0x71, // C,d,E,F
// 	0x08, 0x80              // -, dot(예비)
// };
// 
// static inline void Segment(uint16_t N)
// {
// 	uint8_t d0, d1, d2, d3;
// 	N %= 10000;              // 4자리 제한 (0000~9999)
// 
// 	d3 = N % 10; N /= 10;    // 일
// 	d2 = N % 10; N /= 10;    // 십
// 	d1 = N % 10; N /= 10;    // 백
// 	d0 = N % 10;             // 천
// 
// 	// 멀티플렉싱: 자리당 1ms씩, 30회 반복 ≈ 120ms 표시
// 	for (uint8_t i = 0; i < 30; i++) {
// 		PORTC = 0x0E;        // 천의 자리 ON (PC0만 0)
// 		PORTA = Font[d0];
// 		_delay_ms(1);
// 
// 		PORTC = 0x0D;        // 백의 자리 ON (PC1만 0)
// 		PORTA = Font[d1];
// 		_delay_ms(1);
// 
// 		PORTC = 0x0B;        // 십의 자리 ON (PC2만 0)
// 		PORTA = Font[d2];
// 		_delay_ms(1);
// 
// 		PORTC = 0x07;        // 일의 자리 ON (PC3만 0)
// 		PORTA = Font[d3];
// 		_delay_ms(1);
// 	}
// }
// 
// int main(void)
// {
// 	uint16_t m_cnt;
// 
// 	// PORTA: 세그먼트 데이터(출력), PORTC 하위 4비트: 자리 선택(출력, 액티브-로우)
// 	DDRA = 0xFF;
// 	DDRC = 0x0F;
// 	PORTA = 0x00;    // 공통 캐소드 기준: 세그 OFF = 0
// 	PORTC = 0x0F;    // 모든 자리 OFF (액티브-로우)
// 
// 	// Timer1: 외부 클럭 소스(T1 핀), 상승 에지에서 카운트
// 	// CS12..10 = 111 → External clock source on T1 pin, rising edge
// 	TCCR1A = 0x00;
// 	TCCR1B = 0x07;
// 	TCCR1C = 0x00;
// 	TCNT1  = 0x0000; // 시작값 0
// 
// 	while (1) {
// 		m_cnt = TCNT1;   // 들어온 펄스 수 읽기
// 		Segment(m_cnt);  // FND 표시
// 	}
// }
