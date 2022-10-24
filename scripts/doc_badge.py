from genbadge import Badge
import sys

def make_badge(coverage, ofile):
    perc = int(coverage)
    color = "red" if perc < 50 else "orange" if perc < 75 else "green" if perc < 90 else "bright green"
    b = Badge(left_txt="doc coverage", right_txt=f"{perc}%", color=color)
    b.write_to(ofile, use_shields=False)

if __name__ == "__main__":
    coverage = int(sys.argv[1])
    ofile = sys.argv[2]
    make_badge(coverage, ofile)