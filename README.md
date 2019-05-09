# PA2: Word Counting

Ms. Park은 영어로 써진 글타래가 있을 때, 그곳에 나온 단어들이 각각 몇번 사용되었는지를 찾고, 가장 많이 언급된 단어 순서대로 정렬해서 출력하고 싶었다. github에서 찾은 [https://github.com/AjouOSTA/PA2](https://github.com/AjouOSTA/PA2) repository를 찾은 Ms. Park은 해당 소스코드를 통해 글타래를 분석해 보았으나 분석 속도가 너무 느려서 짜증이 났다.

학부 수업 시간 때 threading과 synchronization을 배웠던 것이 기억난 Ms. Park은 주어진 코드를 병렬화해 속도를 높이기로 한다. Ms. Park이 되어 주어진 word counting 코드를 병렬화 해 보자!

## 입력

- 주어진 텍스트 세 종에 대해서 분석할 것.
- `src/` 이하의 파일을 수정해서 분석할 것 (`Makefile` 수정 금지)
- 아래는 예시 ("Overwatch League", Wikipedia).

[Overwatch League - Wikipedia](https://en.wikipedia.org/wiki/Overwatch_League)

```
The Overwatch League (OWL) is a professional esports league for the video game Overwatch, produced by its developer Blizzard Entertainment. The Overwatch League follows the model of other traditional North American professional sporting leagues by using a set of permanent, city-based teams backed by separate ownership groups. In addition, the league plays in the regular season and playoffs format rather than the use of promotion and relegation used commonly in other esports leagues, with players on the roster being assured a minimum annual salary, benefits, and a portion of winnings and revenue-sharing based on how that team performs. The League was announced in 2016 with its inaugural season taking place in 2018, with a total prize pool of US$3.5 million given to teams that year.
```

## 출력

- ~~`\./data/pass.txt` 에 속해 있는 단어는 카운팅 하지 말 것. (예: 관사, 일부 전치사 및 접속사, be 동사 등)~~
- 모든 단어는 소문자화 하여 카운팅 할 것.
- 특수문자는 모두 지운 후 카운팅 할 것.
- 빈도가 같은 문자열들은 알파벳 순으로 정렬할 것.

```
the 9
a 5
in 5
of 5
and 4
league 4
by 3
with 3
based 2
esports 2
its 2
leagues 2
on 2
other 2
overwatch 2
professional 2
season 2
teams 2
that 2
2016 1
2018 1
3 1
5 1
addition 1
american 1
announced 1
annual 1
assured 1
backed 1
being 1
benefits 1
blizzard 1
city 1
commonly 1
developer 1
entertainment 1
follows 1
for 1
format 1
game 1
given 1
groups 1
how 1
inaugural 1
is 1
million 1
minimum 1
model 1
north 1
owl 1
ownership 1
performs 1
permanent 1
place 1
players 1
playoffs 1
plays 1
pool 1
portion 1
prize 1
produced 1
promotion 1
rather 1
regular 1
relegation 1
revenue 1
roster 1
salary 1
separate 1
set 1
sharing 1
sporting 1
taking 1
team 1
than 1
to 1
total 1
traditional 1
us 1
use 1
used 1
using 1
video 1
was 1
winnings 1
year 1
```

## Hint

- [MapReduce - Wikipedia](https://en.wikipedia.org/wiki/MapReduce)

## Grading

- Deadline: 2019년 5월 30일 오후 11시 59분
- 점수 배분
    - `./data/therepublic.txt` Plato, "The Republic", ~2MB (30%)
    - 영문 Wikipedia의 모든 title, ~1GB (30%)
        * 다운로드: [enwiki-latest-all-titles](https://www.dropbox.com/s/nr2axcscj5ohfr2/enwiki-latest-all-titles?dl=0)
    - 제공된 `./scripts/generate-fake-dataset.py` 를 통해 생성된 ~10GB 파일 (30%)
    - Report (10%)
    - Extra point
        - Amazon Web Services EC2의 a1.xlarge (4 vCPU, 8 MiB, EBS) 기준 각 반의 분석속도 Top 5에게는 extra point 50%
        - 채점 방식: 전체 채점 5회 돌린 후 elapsed time 평균값
