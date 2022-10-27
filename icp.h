Point mass(Cloud measurement);
PointVectorField minDistVectors(Tree map, Cloud measurement);

Vector massTranslation(Point m);
Vector minDistTranslation(PointVectorField minDistVs, float (*kernel)(float));
