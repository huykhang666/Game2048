🎮 2048 – Phiên bản Giáng Sinh 🎄

Môn học: Lập trình hướng đối tượng (OOP) & Cấu trúc dữ liệu
Ngôn ngữ: C++
Công cụ: Visual Studio

🌟 Giới thiệu dự án

Game 2048 là trò chơi trí tuệ nổi tiếng, nơi người chơi trượt các ô số theo 4 hướng để gộp chúng thành ô có giá trị 2048.
Phiên bản này được phát triển bằng C++ hướng đối tượng, chạy trên console, và được thiết kế để áp dụng các kiến thức OOP & cấu trúc dữ liệu đã học.

🧩 Mục tiêu

Hiểu và vận dụng lập trình hướng đối tượng qua việc chia chương trình thành nhiều lớp (Class).

Ứng dụng cấu trúc dữ liệu mảng 2 chiều, thao tác nhập – xuất – lưu file.

Xây dựng luồng xử lý menu – chơi – lưu – kết thúc hoàn chỉnh.

Tạo nền tảng có thể mở rộng lên phiên bản đồ họa (UI đẹp như ảnh mẫu).

🏗️ Cấu trúc chương trình
File	Mô tả
Tile.h / Tile.cpp	Quản lý từng ô số: giá trị, cách hiển thị, gộp ô.
Board.h / Board.cpp	Quản lý toàn bộ bàn chơi: logic di chuyển, sinh ô mới, kiểm tra game over.
Game.h / Game.cpp	Điều khiển luồng chính: menu, render màn chơi, xử lý bàn phím.
Utils.h	Hỗ trợ tiện ích (random, kiểm tra).
save.txt	Lưu tiến trình của người chơi.
main.cpp	Chạy chương trình, khởi tạo đối tượng Game.
💻 Giao diện console

Menu chính: chọn Start / Load / Exit

Màn chơi: hiển thị bảng số, điểm, hướng dẫn điều khiển.

Màn hình kết thúc: thông báo GAME OVER, cho phép chơi lại hoặc thoát.

🎨 Định hướng giao diện đồ họa (UI)

(Dựa trên 3 hình mẫu mà bạn gửi – phiên bản Giáng Sinh)

Màn hình Menu chính

Nền màu xanh tuyết, chữ WELCOME TO 2048.

Nút Start, Load, Exit – thiết kế dạng bo tròn, màu cam.

Nhân vật ông già Noel và quả cầu trang trí xung quanh.

Màn hình Game chính

Lưới 4x4 hiển thị ô số.

Ô được tô màu theo giá trị (2 → vàng nhạt, 128 → cam đậm, 2048 → vàng kim).

Thanh điểm ở trên: Score và Best.

Màn hình Game Over

Dòng chữ GAME OVER! lớn màu đỏ.

Hiển thị điểm hiện tại và điểm cao nhất.

Các nút Play Again, Back to Menu, Exit Game.

Nền tuyết + cây thông + ông già Noel vui nhộn.

⚙️ Kiến thức áp dụng

Lập trình hướng đối tượng (OOP): class, constructor/destructor, encapsulation.

Cấu trúc dữ liệu: mảng 2 chiều, quản lý bộ nhớ động (nếu mở rộng).

Thuật toán: di chuyển và gộp ô logic 2048.

Xử lý file: lưu/đọc dữ liệu từ save.txt.

Tối ưu console: sử dụng _getch() và system("cls") để điều khiển luồng hiển thị.

🚀 Hướng phát triển

Chuyển từ console sang giao diện đồ họa bằng thư viện SFML hoặc SDL.

Thêm hiệu ứng animation khi ô gộp hoặc sinh mới.

Lưu Best Score tự động.

Đưa theme Giáng Sinh vào thực tế (nhạc nền, tuyết rơi, ông già Noel).

Đóng gói thành ứng dụng mini game desktop.

📚 Tài liệu & Tham khảo

Cấu trúc dự án gốc tham khảo từ: https://github.com/iostreamer-X/2048-cpp

Học lập trình OOP C++: https://www.learncpp.com/

Tài liệu SFML (để phát triển giao diện sau): https://www.sfml-dev.org/
