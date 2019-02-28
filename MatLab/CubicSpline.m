function CubicSpline (X,Y,dx)
  
% Input: X is the list of x points
%        Y is the list of y points
%        dx is the derivative at the end points

% Output: Plots results with a coninuous curve
%         includes input points

hold on

title ('Cubic Splines');
plot (X,Y,'bo');

n = length(X); 
cf = csfit(X,Y,dx,0);

a = cf(:,4);
b = cf(:,3);
c = cf(:,2);
d = cf(:,1); 


for i = 1:n-1
    f = @(x) a(i) + b(i) * (x - X(i)) + c(i) * (x - X(i)).^2 + d(i) * (x - X(i)).^3; 
    xf = linspace(X(i),X(i+1));
    plot(xf, f(xf))
end

hold off 
    






