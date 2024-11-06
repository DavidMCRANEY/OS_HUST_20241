# Thư viện Python: `psutil` cho Quản lý Tiến trình

## Mục lục
- [Giới thiệu](#giới-thiệu)
- [Cài đặt](#cài-đặt)
- [Các tính năng chính](#các-tính-năng-chính)
- [Cấu trúc thư viện](#cấu-trúc-thư-viện)
<!-- - [Hướng dẫn sử dụng cơ bản](#hướng-dẫn-sử-dụng-cơ-bản) -->
<!-- - [Ví dụ nâng cao](#ví-dụ-nâng-cao) -->
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
Cài đặt `psutil` qua pip:

```bash
pip install psutil
```
## Các tính năng chính

- Quản lý Tiến trình: Bắt đầu, dừng và giám sát tiến trình hệ thống
- Thông tin Hệ thống: Truy cập CPU, bộ nhớ, ổ đĩa và sử dụng mạng
- Dữ liệu Cảm biến: Lấy dữ liệu nhiệt độ và pin (nếu có)

## Cấu trúc thư viện

`psutil` cung cấp nhiều module và phương thức để tương tác với tài nguyên hệ thống. Các mudole chính bao gồm:
- Process: Tương tác với các tiến trình hệ thống
- CPU: Thu thập thông tin và số liệu liên quan đến CPU
- Memory: Truy cập thông tin về việc sử dụng bộ nhớ hệ thống
- Disk: Lấy thông tin về các phân vùng ổ đĩa và tình trạng sử dụng
- Network: Giám sát I/O mạng và thông tin kết nối
- Sensors: Thu thập dữ liệu từ cảm biến nhiệt độ và pin (nếu có)


## Tham khảo thêm
- [Kho mã nguồn psutil trên GitHub](https://github.com/giampaolo/psutil)
- [Hướng dẫn Python `psutil` trên Real Python](https://realpython.com/python-psutil)

## Tài liệu chính thức
Để có thêm thông tin chi tiết, tham khảo tài liệu chính thức:
- [Tài liệu `psutil`](https://psutil.readthedocs.io/)




