
    inline auto training_image_1_shape = nmtools_tuple{1_ct,1_ct,28_ct,28_ct};
    inline uint8_t training_image_1_flat[784] = {
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
51,
159,
253,
159,
50,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
48,
238,
252,
252,
252,
237,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
54,
227,
253,
252,
239,
233,
252,
57,
6,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
10,
60,
224,
252,
253,
252,
202,
84,
252,
253,
122,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
163,
252,
252,
252,
253,
252,
252,
96,
189,
253,
167,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
51,
238,
253,
253,
190,
114,
253,
228,
47,
79,
255,
168,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
48,
238,
252,
252,
179,
12,
75,
121,
21,
0,
0,
253,
243,
50,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
38,
165,
253,
233,
208,
84,
0,
0,
0,
0,
0,
0,
253,
252,
165,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
7,
178,
252,
240,
71,
19,
28,
0,
0,
0,
0,
0,
0,
253,
252,
195,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
57,
252,
252,
63,
0,
0,
0,
0,
0,
0,
0,
0,
0,
253,
252,
195,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
198,
253,
190,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
255,
253,
196,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
76,
246,
252,
112,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
253,
252,
148,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
85,
252,
230,
25,
0,
0,
0,
0,
0,
0,
0,
0,
7,
135,
253,
186,
12,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
85,
252,
223,
0,
0,
0,
0,
0,
0,
0,
0,
7,
131,
252,
225,
71,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
85,
252,
145,
0,
0,
0,
0,
0,
0,
0,
48,
165,
252,
173,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
86,
253,
225,
0,
0,
0,
0,
0,
0,
114,
238,
253,
162,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
85,
252,
249,
146,
48,
29,
85,
178,
225,
253,
223,
167,
56,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
85,
252,
252,
252,
229,
215,
252,
252,
252,
196,
130,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
28,
199,
252,
252,
253,
252,
252,
233,
145,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
25,
128,
252,
253,
252,
141,
37,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0};
    inline auto training_image_1 = nmtools::array::reshape(training_image_1_flat,training_image_1_shape);
    