;;------------
;;
;;-Exercise 2-
;;
;;------------
;;
;;Write some code that will evaluate a poker hand and determine its rank.


(ns poker-hand-evaluator.core)

(defn in? [seq elem]
  "returns true if elem is in seq"
  (boolean (some #(= % elem) seq)))

(defn suit [[_ s]]
  "returns the suit of a card"
   (str s))

(defn rank [[r _]]
  "return the numeric rank of a card 2-14"
  (def values {\t 10, \j 11, \q 12, \k 13, \a 14, \T 10, \J 11, \Q 12, \K 13, \A 14})
  (if (Character/isDigit r)
    (Integer/valueOf (str r))
    (values r)))

(defn high-card? [hand] true)

(defn pair? [hand]
  "returns true if hand is a pair"
  (let [ranks (map rank hand)]
   (>= (apply max (vals (frequencies ranks))) 2)))


(defn three-of-a-kind? [hand]
  "returns true if hand is a three of a kind"
  (let [ranks (map rank hand)]
   (>= (apply max (vals (frequencies ranks))) 3)))

(defn four-of-a-kind? [hand]
  "returns true if hand is a four of a kind"
  (let [ranks (map rank hand)]
   (>= (apply max (vals (frequencies ranks))) 4)))

(defn flush? [hand]
  "returns true if hand is a flush"
  (let [suits (map suit hand)]
   (== (apply max (vals (frequencies suits))) 5)))

(defn full-house? [hand]
  "returns true if hand is a full house"
  (let [ranks (map rank hand)]
   (= (range 2 4) (sort (vals (frequencies ranks))))))

(defn two-pairs? [hand]
  "returns true if hand is a two pair"
  (let [ranks (map rank hand)]
   (= (seq [1 2 2]) (sort (vals (frequencies ranks))))))

(defn straight? [hand]
  "returns true if hand is a straight"
  (let [ranks   (sort (map rank hand))
        low-ace (sort (replace {14 1} ranks))
        card-range (fn [x] (range (apply min x) (+ (apply max x) 1)))]
    (if (in? ranks 2)
      (= low-ace (card-range low-ace))
      (= ranks (card-range ranks)))))

(defn straight-flush? [hand]
  "returns true if hand is a straight flush"
  (and (straight? hand) (flush? hand)))

(defn royal-flush? [hand]
  "returns true if hand is a royal flush"
  (let [ranks (sort (map rank hand))]
    (and (straight-flush? hand) (= ranks (range 10 15)))))

(defn value [hand]
  "returns the 'value' of a hand 0-9"
  (let [checkers #{[high-card? 0] [pair? 1]
                   [two-pairs? 2] [three-of-a-kind? 3]
                   [straight? 4]  [flush? 5]
                   [full-house? 6][four-of-a-kind? 7]
                   [straight-flush? 8] [royal-flush? 9]}
        hands      (filter #((first %) hand) checkers)]
    (apply max (map second hands))))

(defn poker-hand-evaluator [hand]
  (def hand-values {0 "High Card", 1 "Pair", 2 "Two Pair", 3 "Three of a Kind",
                    4 "Straight", 5 "Flush", 6 "Full House", 7 "Four of a Kind",
                    8 "Straight Flush", 9 "Royal Flush!!!"})
  (hand-values (value hand)))











