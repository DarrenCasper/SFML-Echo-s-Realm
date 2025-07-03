# Project Report

Project ini Dibuat bedasarkan konsep 2d platformer dengan mekanik berpindah realm:
<hr>

## First Commit:
Apa yang ditambahkan:
1. Semacam Tester untuk platform, player dengan ground serta logika untuk 2d platformer
2. Setiap bagian code sudah ditaruh dan dijelaskan (bisa dilihat dari comment yang ada dari kode cpp)
3. Belum diimplementasikan GameState karena ini masih tester untuk platformer
4. Menggunakan Vector untuk menyimpan platform biar bisa banyak initiasi platform
5. Menggunakan logic collision serta set boundaries untuk Teleport player ke ujung map jika sudah menyampai ujung mapnya.

## Second Commit:
Apa yang ditambahkan:
1. Membuat Dissapearring platform yang akan muncul dan tidak muncul dalam spesific waktu (menggunakan fungsi clock dari SFML).
2. Membuat logic untuk class Platform.hpp dan DisappearPlatform.hpp dan bisa memakai vector untuk menyimpan jenis platform yang berbeda tersebut.
3. Mengubah logic collision agar memperhatikan yang mana platform yang active

## Third Commit:
Apa yang ditambahkan:
1. Membuat Realm.hpp dengan Enum class (memakai key = value) di sini Dark dan Light;
2. Membuat RealmPlatform hpp dan Cpp dengan logic mereka.
3. Membenarkan Fungsi di Main untuk menghandle Realm, serta BG diubah bedasarkan Realm player berada. 
4. Tadi out of bounds sempet hilang tapi udah di restore lagi.

## Fourth Commit:
apa yang ditambahkan:
1. Membuat class Object yang bisa menyimpan banyak objek (jadi nanti bisa buat turunan dari object).
2. Membuat cloud yang bergerak dari kiri ke kanan dan di wrap balik (inheritance dari object)
3. Mungkin nanti menambahkan dekorasi map agar map lebih enak dilihatnya.
4. Menggunakan Vector lagi untuk setor antara object atau class dari Cloud.s

## Fifth Commit:
Apa yang ditambahkan:
1. Membuat Sprite buat player
2. Rencana mau kasih sprite buat objek tapi cukup susah karena image yang dipake di stretch semua sehingga mungkin tetap menggunakan platform berwarna rectangle
3. Logic player sudah diupdate tetapi tidak menggunakan banyak animasi hanya animasi bergerak dan arah yang dihadap ketika dipencet A dan D.


## Sixth Commit:
Apa yang ditambahkan:
1. Membuat texture untuk platform yang berubah bedasarkan platform tersebut
2. Platform yang awalnya cumang rectangle diubah jadi texture pixel (walaupun scale agak berantakan)
3. Rencana Tinggal membuat game state dan beberapa objek agar bisa menyelesaikan level 1 (main per level)

## Seventh Commit:
Apa yang ditambahkan:
1. Menggabungkan GameState, MenuState, dan State lain ke dalam program normal.
2. Membenarkan gravity yang awalnya dikali dengan deltatime (karena akan akumulasi seiring waktu di menu yang akan membuat phasing)
3. Sudah berhasil berjalan gamenya jadi tinggal di add fungsi lain yang diinginkan

## Eight Commit:
Apa yang ditambahkan:
1. Membuat Splash State dan mengubah logo 
2. Mengubah Menu state agar memiliki text dan title game yang jelas
3. Membuat Class RealmObstacle, yang menutup player jika di realm yang salah.
4. Membenarkan logika collision player dengan realm obstacle karena awalnya scale player yang kurang bagus.

## Ninth Commit:
Apa yang ditambahkan:
1. Membuat level akhir dan memasang semua platform
2. Menambahkan object spike dan star yang merupakan suatu kondisi untuk trigger state lain.
3. mengubah get_next_State di dalam game_state (belum dibuat state akhir yaitu game over state dan you win state)
4. membenarkan RealmObstacle, dan logic collision handling terhadap spike dan star (sering ngebug ini cuman udah meningan)

## Tenth Commit: (Last Commit)
Apa yang ditambahkan:
1. Menambahkan State Game over dan ending state
2. Kedua state tersebut menggunakan menu state sebagai base template
3. membenarkan lag atau delay di clock time pada saat player menyentuh spike atau star agar tidak ngebug
