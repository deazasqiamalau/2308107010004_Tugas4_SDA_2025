# Tugas 04 Struktur Data dan Algoritma - Analisis Algoritma Pengurutan
- **Nama:** Dea Zasqia Pasaribu Malau
- **NPM:** 2308107010004
- **Jurusan:** Informatika
- **Fakultas:** Matematika dan Ilmu Pengetahuan Alam
- **Universitas:** Universitas Syiah Kuala

## Deskripsi Tugas
Tugas ini merupakan implementasi dan analisis performa dari enam algoritma pengurutan:
1. Bubble Sort
2. Selection Sort
3. Insertion Sort
4. Merge Sort
5. Quick Sort
6. Shell Sort

Analisis difokuskan pada dua aspek utama:
- Waktu eksekusi
- Penggunaan memori

Algoritma diuji menggunakan dataset dengan ukuran bervariasi (10.000 hingga 2.000.000 elemen) dan dua jenis data:
- Data angka acak
- Data kata acak

## Struktur Direktori
- `src/` - Berisi implementasi semua algoritma pengurutan
- `data/` - Berisi dataset yang digunakan untuk pengujian
- `results/` - Berisi hasil pengujian dalam bentuk tabel dan grafik
- `docs/` - Berisi laporan lengkap dan dokumentasi

## Cara Menjalankan
1. Pastikan compiler C sudah terinstal di sistem Anda
2. Kompilasi program dengan perintah: `gcc -o sorting_test main.c`
3. Jalankan program dengan perintah: `./sorting_test`

## Hasil Utama
Hasil eksperimen menunjukkan:
1. Algoritma O(n²) (Bubble Sort, Selection Sort, Insertion Sort) menunjukkan peningkatan waktu eksekusi yang drastis seiring bertambahnya ukuran data.
2. Algoritma O(n log n) (Merge Sort, Quick Sort, Shell Sort) menunjukkan performa yang jauh lebih baik pada data berukuran besar.
3. Quick Sort secara konsisten menunjukkan performa terbaik dalam hal waktu eksekusi.
4. Merge Sort memerlukan penggunaan memori yang lebih tinggi karena kebutuhan ruang tambahan O(n).
5. Pengurutan data kata memerlukan waktu eksekusi dan penggunaan memori yang lebih tinggi dibandingkan data angka.

## Kesimpulan
Pemilihan algoritma pengurutan yang tepat sangat bergantung pada karakteristik data, ukuran dataset, dan batasan sumber daya. Untuk dataset berukuran besar, algoritma dengan kompleksitas O(n log n) seperti Quick Sort dan Merge Sort jauh lebih direkomendasikan dibandingkan algoritma O(n²) seperti Bubble Sort, Selection Sort, dan Insertion Sort.
Berdasarkan hasil eksperimen dan analisis yang telah dilakukan, dapat ditarik beberapa kesimpulan:
### 1.	Korelasi Kompleksitas Teoretis dengan Performa Praktis
- Hasil eksperimen menunjukkan korelasi yang kuat antara kompleksitas teoretis algoritma dengan performa praktisnya.
- Algoritma dengan kompleksitas O(n²) (Bubble Sort, Selection Sort, Insertion Sort) menunjukkan peningkatan waktu eksekusi yang drastis seiring dengan bertambahnya ukuran data.
-	Algoritma dengan kompleksitas O(n log n) (Merge Sort, Quick Sort, Shell Sort) menunjukkan performa yang jauh lebih baik pada data berukuran besar.
### 2.	Perbandingan Algoritma Pengurutan** 
-	Quick Sort secara konsisten menunjukkan performa terbaik dalam hal waktu eksekusi, terutama pada dataset berukuran besar.
-	Merge Sort menunjukkan performa yang hampir setara dengan Quick Sort dalam waktu eksekusi, namun dengan penggunaan memori yang lebih tinggi.
-	Shell Sort menawarkan keseimbangan yang baik antara kompleksitas implementasi, penggunaan memori, dan waktu eksekusi.
-	Insertion Sort adalah pilihan terbaik di antara algoritma O(n²), terutama untuk dataset berukuran kecil atau hampir terurut.
-	Bubble Sort dan Selection Sort tidak direkomendasikan untuk dataset berukuran besar karena performa yang sangat buruk.
### 3.	Pengaruh Jenis Data
-	Pengurutan data kata konsisten memerlukan waktu eksekusi yang lebih lama dibandingkan dengan pengurutan data angka, karena kompleksitas operasi perbandingan string.
-	Penggunaan memori untuk data kata signifikan lebih tinggi dibandingkan dengan data angka, yang menunjukkan pentingnya mempertimbangkan jenis data dalam pemilihan algoritma pengurutan.
### 4.	Rekomendasi Penggunaan Algoritma
-	Untuk dataset berukuran kecil (< 10.000 elemen), semua algoritma dapat digunakan dengan waktu eksekusi yang masih dapat diterima.
-	Untuk dataset berukuran sedang (10.000 - 100.000 elemen), Insertion Sort masih dapat dipertimbangkan jika kesederhanaan implementasi menjadi prioritas, namun algoritma O(n log n) mulai menunjukkan keunggulan signifikan.
-	Untuk dataset berukuran besar (> 100.000 elemen), hanya algoritma O(n log n) yang praktis digunakan, dengan Quick Sort sebagai pilihan terbaik jika kasus terburuk O(n²) dapat dihindari (misalnya dengan pemilihan pivot secara acak).
### 5.	Trade-off Waktu dan Memori
-	Terdapat trade-off antara efisiensi waktu dan penggunaan memori, yang terilustrasikan dengan jelas pada Merge Sort yang memerlukan ruang memori tambahan namun memberikan performa waktu yang sangat baik.
-	Dalam lingkungan dengan batasan memori yang ketat, Quick Sort atau Shell Sort dapat menjadi pilihan yang lebih baik dibandingkan dengan Merge Sort.
Eksperimen ini menunjukkan pentingnya pemilihan algoritma pengurutan yang tepat berdasarkan karakteristik data, ukuran dataset, dan batasan sumber daya yang ada. Algoritma yang efisien secara teoretis terbukti memberikan performa yang jauh lebih baik pada praktiknya, terutama ketika berhadapan dengan dataset berukuran besar.

