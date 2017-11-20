def hamming_distance(str_1, str_2):
  mismatches = 0

  if len(str_1) != len(str_2):
    raise ValueError('Strings are not of equal length')

  for i in range(len(str_1)):
    if str_1[i] != str_2[i]:
      mismatches += 1

  return mismatches

print hamming_distance("AGTAGG", "AGTAGA")