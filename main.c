#include <stdio.h>
#include <string.h>

struct FlightTicket {
    char pnrCode[15];
    char passengerName[50];
    int ticketClass;       
    float baggageWeight;
    float baggageFee;
};

int main() {
    struct FlightTicket danhSachVe[100];
    int soLuong = 0;
    int luaChon;

    do {
        printf("\n=== HE THONG BAN VE VA CHECK-IN MAY BAY ===\n");
        printf("1. Them ve may bay moi\n");
        printf("2. Hien thi danh sach ve\n");
        printf("3. Cap nhat hanh ly theo PNR\n");
        printf("4. Xoa ve theo PNR\n");
        printf("5. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &luaChon);
        while (getchar() != '\n'); // xoa bo dem tranh troi lenh

        switch (luaChon) {
            case 1: {
                // Kiem tra mang day chua
                if (soLuong >= 100) {
                    printf("Danh sach ve da day, khong the them moi!\n");
                    break;
                }

                printf("\n--- Them ve thu %d ---\n", soLuong + 1);

                // Nhap ma PNR (khong co khoang trang)
                printf("Nhap ma PNR: ");
                scanf("%14s", danhSachVe[soLuong].pnrCode);
                while (getchar() != '\n');

                // Nhap ho ten bang fgets
                printf("Nhap ho ten hanh khach: ");
                fgets(danhSachVe[soLuong].passengerName, sizeof(danhSachVe[soLuong].passengerName), stdin);
                danhSachVe[soLuong].passengerName[strcspn(danhSachVe[soLuong].passengerName, "\n")] = '\0'; // cat bo \n

                // Nhap hang ve (1, 2 hoac 3)
                do {
                    printf("Nhap hang ve (1-Eco, 2-Deluxe, 3-Business): ");
                    scanf("%d", &danhSachVe[soLuong].ticketClass);
                    while (getchar() != '\n');
                } while (danhSachVe[soLuong].ticketClass < 1 || danhSachVe[soLuong].ticketClass > 3);

                printf("Nhap khoi luong hanh ly (kg): ");
                scanf("%f", &danhSachVe[soLuong].baggageWeight);
                while (getchar() != '\n');

                // Tinh phi phu thu theo quy dinh
                if (danhSachVe[soLuong].ticketClass == 3) {
                    danhSachVe[soLuong].baggageFee = 0.0f; // Business duoc mien phi
                } else {
                    if (danhSachVe[soLuong].baggageWeight > 7.0f) {
                        danhSachVe[soLuong].baggageFee = (danhSachVe[soLuong].baggageWeight - 7.0f) * 50000.0f;
                    } else {
                        danhSachVe[soLuong].baggageFee = 0.0f;
                    }
                }

                printf("=> Them ve thanh cong! Cuoc phat hanh ly qua can: %.0f VND.\n", danhSachVe[soLuong].baggageFee);
                soLuong++; // tang bien dem ve
                break;
            }

            case 2: {
                // In danh sach dang bang
                if (soLuong == 0) {
                    printf("Danh sach ve dang rong!\n");
                    break;
                }

                printf("\n========================================================================================\n");
                printf("%-5s | %-10s | %-25s | %-10s | %-14s | %-15s\n", 
                       "STT", "Ma PNR", "Ho ten hanh khach", "Hang ve", "Hanh ly (kg)", "Cuoc qua cuoc");
                printf("========================================================================================\n");

                for (int i = 0; i < soLuong; i++) {
                    char tenHangVe[15];
                    if (danhSachVe[i].ticketClass == 1) strcpy(tenHangVe, "Eco");
                    else if (danhSachVe[i].ticketClass == 2) strcpy(tenHangVe, "Deluxe");
                    else strcpy(tenHangVe, "Business");

                    printf("%-5d | %-10s | %-25s | %-10s | %-14.1f | %.0f VND\n",
                           i + 1,
                           danhSachVe[i].pnrCode,
                           danhSachVe[i].passengerName,
                           tenHangVe,
                           danhSachVe[i].baggageWeight,
                           danhSachVe[i].baggageFee);
                }
                printf("========================================================================================\n");
                break;
            }

            case 3: {
                // Cap nhat hanh ly theo PNR
                if (soLuong == 0) {
                    printf("Danh sach ve dang rong!\n");
                    break;
                }

                char pnrTim[15];
                printf("Nhap ma PNR can cap nhat hanh ly: ");
                scanf("%14s", pnrTim);
                while (getchar() != '\n');

                int index = -1;
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(danhSachVe[i].pnrCode, pnrTim) == 0) {
                        index = i;
                        break;
                    }
                }

                if (index != -1) {
                    printf("Tim thay hanh khach: %s\n", danhSachVe[index].passengerName);
                    printf("Nhap trong luong hanh ly moi (kg): ");
                    scanf("%f", &danhSachVe[index].baggageWeight);
                    while (getchar() != '\n');

                    // Tinh lai phi phu thu
                    if (danhSachVe[index].ticketClass == 3) {
                        danhSachVe[index].baggageFee = 0.0f;
                    } else {
                        if (danhSachVe[index].baggageWeight > 7.0f) {
                            danhSachVe[index].baggageFee = (danhSachVe[index].baggageWeight - 7.0f) * 50000.0f;
                        } else {
                            danhSachVe[index].baggageFee = 0.0f;
                        }
                    }

                    printf("=> Cap nhat thanh cong! Phi hanh ly qua cuoc moi: %.0f VND.\n", danhSachVe[index].baggageFee);
                } else {
                    printf("Khong tim thay ve co ma PNR da nhap!\n");
                }
                break;
            }

            case 4: {
                // Xoa ve bang thuat toan don mang
                if (soLuong == 0) {
                    printf("Danh sach ve dang rong!\n");
                    break;
                }

                char pnrXoa[15];
                printf("Nhap ma PNR can xoa: ");
                scanf("%14s", pnrXoa);
                while (getchar() != '\n');

                int indexXoa = -1;
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(danhSachVe[i].pnrCode, pnrXoa) == 0) {
                        indexXoa = i;
                        break;
                    }
                }

                if (indexXoa != -1) {
                    // Don cac phan tu phia sau len truoc de de len phan tu bi xoa
                    for (int i = indexXoa; i < soLuong - 1; i++) {
                        danhSachVe[i] = danhSachVe[i + 1];
                    }
                    soLuong--; // giam so luong ve di 1
                    printf("=> Da xoa thanh cong ve co ma PNR: %s ra khoi he thong.\n", pnrXoa);
                } else {
                    printf("Khong tim thay ve co ma PNR da nhap!\n");
                }
                break;
            }

            case 5:
                printf("\nCam on ban da su dung chuong trinh! Tam biet!\n");
                break;

            default:
                printf("Lua chon khong hop le, vui long chon tu 1 den 5!\n");
                break;
        }

    } while (luaChon != 5);

    return 0;
}
