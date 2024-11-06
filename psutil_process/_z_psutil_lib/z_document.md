# Thư viện Python: `psutil` cho Quản lý Tiến trình

## Mục lục
- [Giới thiệu](#giới-thiệu)
- [Cài đặt](#cài-đặt)
- [Các tính năng chính](#các-tính-năng-chính)
- [Cấu trúc thư viện](#cấu-trúc-thư-viện)
- [Hướng dẫn sử dụng cơ bản](#hướng-dẫn-sử-dụng-cơ-bản)
- [Ví dụ nâng cao](#ví-dụ-nâng-cao)
- [Tham khảo thêm](#tham-khảo-thêm)
- [Tài liệu chính thức](#tài-liệu-chính-thức)

---

## Giới thiệu
### Tổng quan
`psutil` (Python System and Process Utilities) là một thư viện đa nền tảng giúp lấy thông tin về việc sử dụng tài nguyên hệ thống (CPU, bộ nhớ, ổ đĩa, mạng, cảm biến) và các tiến trình. Thư viện rất hữu ích cho việc giám sát hệ thống, phân tích hiệu năng, và quản lý tài nguyên của tiến trình.

### Lợi ích của `psutil`
- Quản lý và giám sát tài nguyên hệ thống hiệu quả
- Lấy thông tin chi tiết về tiến trình và thực hiện các thao tác như dừng hoặc tạm ngừng tiến trình
- Phù hợp để xây dựng công cụ giám sát hệ thống và tự động hóa

## Cài đặt
Bạn có thể cài đặt `psutil` qua pip:

```bash
pip install psutil




