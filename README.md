# 🎄 2048 - Phiên bản Giáng Sinh 🎮  
> Một dự án OOP & Cấu trúc dữ liệu bằng C++, mang không khí Giáng Sinh đến trò chơi kinh điển 2048!  

![Main Menu]()
![Gameplay](tại nền cho game 2048 phiên bản giáng sinh _ GIAO DIỆN 1 – MENU CHÍNH__Tổng thể___Title lớn ở trên (20%)__Danh sách nút chọn (60%)__Chữ hướng dẫn hoặc bản quyền (20%)__Chi tiết tỉ lệ___Khu vực_Tỷ lệ_Gợi ý p (1).jpg)
![Game Over](end2048.jpg)

---

## 🧩 Giới thiệu dự án

Game **2048** là trò chơi trí tuệ nổi tiếng, nơi người chơi trượt các ô số để hợp nhất chúng thành ô **2048**.  
Phiên bản này được viết bằng **C++ hướng đối tượng**, chạy trên **console**, với phong cách **Giáng Sinh vui nhộn**.  

🎯 Mục tiêu của dự án:
- Ứng dụng kiến thức **Lập trình Hướng đối tượng (OOP)** và **Cấu trúc dữ liệu (Data Structure)**.
- Xây dựng dự án **đa file, dễ bảo trì và mở rộng**.
- Phát triển **logic hoàn chỉnh** của game 2048 từ đầu, không dùng thư viện ngoài.
- Đặt nền móng cho **phiên bản đồ họa trong tương lai (SFML / SDL)**.

---

## 🏗️ Kiến trúc chương trình

| 🧱 File | 📖 Mô tả |
|:--------|:---------|
| **Tile.h / Tile.cpp** | Quản lý từng ô trên bảng (giá trị, hiển thị, gộp ô). |
| **Board.h / Board.cpp** | Xử lý toàn bộ logic trò chơi: di chuyển, sinh ô mới, kiểm tra thắng/thua. |
| **Game.h / Game.cpp** | Quản lý luồng chính: hiển thị, menu, nhập phím, vòng lặp chơi. |
| **Utils.h** | Các hàm tiện ích: random, reset, hỗ trợ xuất dữ liệu. |
| **save.txt** | File lưu tiến trình và điểm số của người chơi. |
| **main.cpp** | Điểm bắt đầu chương trình – khởi tạo và chạy game. |

---

## 💻 Cách điều khiển
| Phím | Chức năng |
|------|------------|
| ⬆️ / ⬇️ / ⬅️ / ➡️ | Di chuyển ô số |
| **S** | Lưu tiến trình |
| **L** | Tải game đã lưu |
| **Q** | Thoát game |

---

## 🌲 Giao diện Console
- **Menu chính:** chọn `Start`, `Load`, `Exit`.  
- **Màn chơi:** hiển thị lưới 4x4, điểm hiện tại, hướng dẫn.  
- **Kết thúc:** dòng *GAME OVER!* và lựa chọn *Play Again* hoặc *Thoát*.  

---

## 🎨 Hướng phát triển giao diện (UI Giáng Sinh)

| Màn hình | Mô tả |
|-----------|--------|
| 🏠 **Menu chính** | Nền tuyết xanh, tiêu đề *WELCOME TO 2048*, nút cam bo tròn (Start, Load, Exit), ông già Noel đứng góc dưới. |
| 🎮 **Gameplay** | Lưới 4x4 màu vàng đồng, ô đổi màu theo giá trị (2→vàng nhạt, 128→cam, 2048→vàng kim). |
| 🧊 **Game Over** | Dòng chữ đỏ "GAME OVER!", hiển thị điểm và nút "Play Again" – nền tuyết trắng rơi, cây thông & đèn Giáng Sinh. |

> 💡 Giao diện được phác thảo trong ba hình minh họa phía trên.

---

## ⚙️ Kiến thức áp dụng
- **OOP:** Class, Encapsulation, Constructor/Destructor, Function Overloading.  
- **Cấu trúc dữ liệu:** Mảng 2 chiều, quản lý trạng thái ô, thuật toán di chuyển & gộp.  
- **Thuật toán:** Kiểm tra hợp lệ, sinh ô ngẫu nhiên, xác định thắng/thua.  
- **Xử lý file:** Ghi/đọc `save.txt` để lưu tiến trình người chơi.  
- **Console Control:** `_getch()`, `system("cls")`, thao tác bàn phím và xóa màn hình.

---

## 🚀 Định hướng phát triển
✅ Chuyển sang **phiên bản đồ họa (SFML hoặc SDL2)**.  
✅ Thêm **animation khi gộp ô** và **hiệu ứng tuyết rơi**.  
✅ Lưu **Best Score** tự động.  
✅ Cập nhật **giao diện Giáng Sinh đầy đủ âm thanh, hiệu ứng**.  
✅ Phát hành dưới dạng **mini game desktop**.

---

## 🧠 Bài học đạt được
- Hiểu rõ cách thiết kế class và tách file hợp lý.  
- Thực hành **nguyên lý OOP (Encapsulation, Reusability)**.  
- Tư duy **xử lý logic và cấu trúc dữ liệu trong game**.  
- Biết cách tổ chức, debug và tối ưu project C++.  

---

## 📚 Tài liệu & Tham khảo
- Mẫu logic tham khảo: [https://github.com/iostreamer-X/2048-cpp](https://github.com/iostreamer-X/2048-cpp)  
- Học C++ & OOP: [https://www.learncpp.com/](https://www.learncpp.com/)  
- Tài liệu SFML (để phát triển UI): [https://www.sfml-dev.org/](https://www.sfml-dev.org/)  

---

## 👨‍💻 Tác giả
**Nguyễn Huy Khang - Trần Thảo Nương - Nguyễn Ngọc Ngà** – Sinh viên Công nghệ Thông tin, Trường Đại học Giao thông Vận tải – Phân hiệu TP.HCM (UTC2)  
> "2048 Giáng Sinh – Bước đầu xây dựng game bằng C++ hướng đối tượng và hướng tới giao diện chuyên nghiệp hơn."

---

🎅 *Chúc bạn chơi vui vẻ & Merry Christmas!* 🎄  
