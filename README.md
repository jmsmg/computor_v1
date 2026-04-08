# Computor v1

2차 이하 다항식 방정식을 푸는 프로그램

## 기능

- 방정식을 축약된 형태(Reduced form)로 출력
- 다항식의 차수(Polynomial degree) 출력
- 방정식의 해(Solution) 계산 및 출력
- 2차 방정식의 경우 판별식(Discriminant) 부호에 따른 처리
  - 양수: 서로 다른 두 실근
  - 0: 중근
  - 음수: 복소수 해

## 빌드

```bash
make
```

## 사용법

```bash
./computor "방정식"
```

### 입력 형식

각 항은 `a * X^p` 형식을 따릅니다.
- `a`: 계수 (정수 또는 소수)
- `p`: 지수 (0, 1, 2)

### 예시

**2차 방정식 (판별식 > 0)**
```bash
./computor "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"
# Reduced form: 4 * X^0 + 4 * X^1 - 9.3 * X^2 = 0
# Polynomial degree: 2
# Discriminant is strictly positive, the two solutions are:
# 0.905239
# -0.475131
```

**1차 방정식**
```bash
./computor "5 * X^0 + 4 * X^1 = 4 * X^0"
# Reduced form: 1 * X^0 + 4 * X^1 = 0
# Polynomial degree: 1
# The solution is:
# -0.25
```

**3차 이상 (미지원)**
```bash
./computor "8 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^3 = 3 * X^0"
# Reduced form: 5 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^3 = 0
# Polynomial degree: 3
# The polynomial degree is strictly greater than 2, I can't solve.
```

## 특수 케이스

| 케이스 | 예시 | 결과 |
|--------|------|------|
| 무한해 | `42 * X^0 = 42 * X^0` | 모든 실수가 해 |
| 해 없음 | `1 * X^0 = 0 * X^0` | 해가 존재하지 않음 |
| 복소수 해 | 판별식 < 0 | a + bi, a - bi 형태 출력 |
